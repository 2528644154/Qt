#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mdichild.h"
#include <QMdiSubWindow>
#include <QFileDialog>
#include <QSignalMapper>
#include <QMessageBox>
#include <QSettings>
#include <QCloseEvent>
#include <QLabel>
#include <qtextcodec.h>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <QPlainTextEdit>
#include <QTextEdit>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actionSeparator = new QAction(this); // ��������������
    actionSeparator->setSeparator(true); // ���������ü�����
    updateMenus();   // ���²˵�
    connect(ui->mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,
            SLOT(updateMenus()));  // ���л����ʱ���²˵�

    windowMapper = new QSignalMapper(this); // �����ź�ӳ����
    connect(windowMapper, SIGNAL(mapped(QWidget*)), // ӳ�������·����ź�
            this, SLOT(setActiveSubWindow(QWidget*))); // ���û����

    // ���´��ڲ˵����������õ����ڲ˵���Ҫ��ʾ��ʱ�����´��ڲ˵�
    updateWindowMenu();
    connect(ui->menuW,SIGNAL(aboutToShow()),this,SLOT(updateWindowMenu()));


    readSettings(); // ��ʼ����ʱ��ȡ����������Ϣ
    initWindow(); // ��ʼ������
}



QTextCodec *codec = QTextCodec::codecForName("GB2312");
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()  // �½��ļ��˵�
{
    MdiChild *child = createMdiChild(); // ����MdiChild
    child->newFile(); // �½��ļ�
    child->show(); // ��ʾ�Ӵ���
}

MdiChild * MainWindow::createMdiChild() // �����Ӵ��ڲ���
{
    MdiChild *child = new MdiChild; // ����MdiChild����
    ui->mdiArea->addSubWindow(child); // �����ĵ����������Ӵ��ڣ�childΪ���Ĳ���

    // ����QTextEdit�����Ƿ����Ը����ź����ü��и��ƶ����Ƿ�����
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCut,
            SLOT(setEnabled(bool)));
    connect(child,SIGNAL(copyAvailable(bool)),ui->actionCopy,
            SLOT(setEnabled(bool)));

    // ����QTextDocument�����Ƿ����Գ����ָ��ź����ó����ָ������Ƿ�����
    connect(child->document(),SIGNAL(undoAvailable(bool)),
            ui->actionUndo,SLOT(setEnabled(bool)));
    connect(child->document(),SIGNAL(redoAvailable(bool)),
            ui->actionRedo,SLOT(setEnabled(bool)));

    // ÿ���༭���еĹ���λ�øı䣬��������ʾ�кź��к�
    connect(child,SIGNAL(cursorPositionChanged()),this,SLOT(showTextRowAndCol()));

    return child;
}

void MainWindow::updateMenus() // ���²˵�
{
    bool hasMdiChild = (activeMdiChild() != 0); // �Ƿ��л����
    ui->actionSave->setEnabled(hasMdiChild);   // ���ø��������Ƿ�����
    ui->actionSaveAs->setEnabled(hasMdiChild);
    ui->actionPaste->setEnabled(hasMdiChild);
    ui->actionClose->setEnabled(hasMdiChild);
    ui->actionCloseAll->setEnabled(hasMdiChild);
    ui->actionTile->setEnabled(hasMdiChild);
    ui->actionCascade->setEnabled(hasMdiChild);
    ui->actionNext->setEnabled(hasMdiChild);
    ui->actionPrevious->setEnabled(hasMdiChild);
    actionSeparator->setVisible(hasMdiChild); // ���ü������Ƿ���ʾ

    bool hasSelection = (activeMdiChild()
                         && activeMdiChild()->textCursor().hasSelection());

    // �л�������б�ѡ�����ı������и��Ʋſ���
    ui->actionCut->setEnabled(hasSelection);
    ui->actionCopy->setEnabled(hasSelection);

    ui->actionUndo->setEnabled(activeMdiChild() // �л�������ĵ��г�������
                          && activeMdiChild()->document()->isUndoAvailable());
    ui->actionRedo->setEnabled(activeMdiChild() // �л�������ĵ��лָ�����
                          && activeMdiChild()->document()->isRedoAvailable());
}

MdiChild * MainWindow::activeMdiChild() // �����
{
    // �����л���ڣ��������ڵ����Ĳ���ת��ΪMdiChild����
    if (QMdiSubWindow *activeSubWindow = ui->mdiArea->activeSubWindow())
        return qobject_cast<MdiChild *>(activeSubWindow->widget());
    return 0; // û�л���ڣ�ֱ�ӷ���0
}

void MainWindow::on_actionOpen_triggered() // �����ļ��˵�
{
    QString fileName = QFileDialog::getOpenFileName(this); // ��ȡ�ļ�·��
    if (!fileName.isEmpty()) { // ����·����Ϊ�գ����鿴���ļ��Ƿ��Ѿ�����
        QMdiSubWindow *existing = findMdiChild(fileName);
        if (existing) { // �����Ѿ����ڣ��򽫶�Ӧ���Ӵ�������Ϊ�����
            ui->mdiArea->setActiveSubWindow(existing);
            return;
        }

        MdiChild *child = createMdiChild(); // ����û�д򿪣����½��Ӵ���
        if (child->loadFile(fileName)) {
            ui->statusBar->showMessage(codec->toUnicode("�����ļ��ɹ�"), 2000);
            child->show();
        } else {
            child->close();
        }
    }
}

QMdiSubWindow * MainWindow::findMdiChild(const QString &fileName) // �����Ӵ���
{

    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();

    // ����foreach���������Ӵ����б����������ļ�·����Ҫ���ҵ�·����ͬ���򷵻ظô���
    foreach (QMdiSubWindow *window, ui->mdiArea->subWindowList()) {
        MdiChild *mdiChild = qobject_cast<MdiChild *>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return 0;
}

void MainWindow::setActiveSubWindow(QWidget *window) // ���û�Ӵ���
{
    if (!window) // ���������˴��ڲ���������������Ϊ�����
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::updateWindowMenu() // ���´��ڲ˵�
{
    ui->menuW->clear(); // �����ղ˵���Ȼ�������Ӹ����˵�����
    ui->menuW->addAction(ui->actionClose);
    ui->menuW->addAction(ui->actionCloseAll);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionTile);
    ui->menuW->addAction(ui->actionCascade);
    ui->menuW->addSeparator();
    ui->menuW->addAction(ui->actionNext);
    ui->menuW->addAction(ui->actionPrevious);
    ui->menuW->addAction(actionSeparator);

    QList<QMdiSubWindow *> windows = ui->mdiArea->subWindowList();
    actionSeparator->setVisible(!windows.isEmpty());
    // �����л���ڣ�����ʾ������
    for (int i = 0; i < windows.size(); ++i) { // ���������Ӵ���
        MdiChild *child = qobject_cast<MdiChild *>(windows.at(i)->widget());

        QString text;
        if (i < 9) { // ����������С��9�������ñ���Ϊ���ݼ�
            text = tr("&%1 %2").arg(i + 1)
                               .arg(child->userFriendlyCurrentFile());
        } else {
            text = tr("%1 %2").arg(i + 1)
                              .arg(child->userFriendlyCurrentFile());
        }
        QAction *action  = ui->menuW->addAction(text); // ���Ӷ������˵�
        action->setCheckable(true); // ���ö�������ѡ��

        // ���õ�ǰ����ڶ���Ϊѡ��״̬
        action ->setChecked(child == activeMdiChild());

        // ���������Ĵ����źŵ��ź�ӳ������map()�ۺ����ϣ����������ᷢ��mapped()�ź�
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));

        // ����������Ӧ�Ĵ��ڲ�������ӳ�䣬�ڷ���mapped()�ź�ʱ�ͻ����������ڲ���Ϊ����
        windowMapper->setMapping(action, windows.at(i));

    }
}

/********************1.3.3С�ڶ�������Щ���������˲���ʡ��****************************************/

void MainWindow::on_actionSave_triggered() // �����˵�
{
    if(activeMdiChild() && activeMdiChild()->save())
        ui->statusBar->showMessage(codec->toUnicode("�ļ������ɹ�"),2000);
}

void MainWindow::on_actionSaveAs_triggered()  // ����Ϊ�˵�
{
    if(activeMdiChild() && activeMdiChild()->saveAs())
        ui->statusBar->showMessage(codec->toUnicode("�ļ������ɹ�"),2000);
}

void MainWindow::on_actionUndo_triggered() // �����˵�
{
    if(activeMdiChild()) activeMdiChild()->undo();
}

void MainWindow::on_actionRedo_triggered() // �ָ��˵�
{
    if(activeMdiChild()) activeMdiChild()->redo();
}

void MainWindow::on_actionCut_triggered() // ���в˵�
{
    if(activeMdiChild()) activeMdiChild()->cut();
}

void MainWindow::on_actionCopy_triggered() // ���Ʋ˵�
{
    if(activeMdiChild()) activeMdiChild()->copy();
}

void MainWindow::on_actionPaste_triggered() // ճ���˵�
{
    if(activeMdiChild()) activeMdiChild()->paste();
}

void MainWindow::on_actionClose_triggered() // �رղ˵�
{
    ui->mdiArea->closeActiveSubWindow();
}

void MainWindow::on_actionCloseAll_triggered() // �ر����д��ڲ˵�
{
    ui->mdiArea->closeAllSubWindows();
}

void MainWindow::on_actionTile_triggered() // ƽ�̲˵�
{
    ui->mdiArea->tileSubWindows();
}

void MainWindow::on_actionCascade_triggered() // �����˵�
{
    ui->mdiArea->cascadeSubWindows();
}

void MainWindow::on_actionNext_triggered() // ��һ���˵�
{
    ui->mdiArea->activateNextSubWindow();
}

void MainWindow::on_actionPrevious_triggered() // ǰһ���˵�
{
    ui->mdiArea->activatePreviousSubWindow();
}

void MainWindow::on_actionAbout_triggered() // ���ڲ˵�
{
    QMessageBox::about(this,codec->toUnicode("���ڱ�����"),codec->toUnicode("��ӭ�����ҵ�csdn��ҳ��https://blog.csdn.net/qq_46424406?spm=1003.2020.3001.5343"));
}

//void MainWindow::on_actionAboutQt_triggered() // ����Qt�˵�
//{
//    qApp->aboutQt(); // ������qApp��QApplication������ȫ��ָ�룬
//                     // ���д����൱��QApplication::aboutQt();
//}



void MainWindow::on_actionExit_triggered() // �˳��˵�
{
    qApp->closeAllWindows(); // �ȼ���QApplication::closeAllWindows();
}

void MainWindow::closeEvent(QCloseEvent *event) // �ر��¼�
{
    ui->mdiArea->closeAllSubWindows(); // ��ִ�ж��ĵ������Ĺرղ���
    if (ui->mdiArea->currentSubWindow()) {
        event->ignore(); // �������д���û�йرգ������Ը��¼�
    } else {
        writeSettings(); // �ڹر�ǰд�봰������
        event->accept();
    }
}

void MainWindow::writeSettings() // д�봰������
{
    QSettings settings("yafeilinux", "myMdi");
    settings.setValue("pos", pos());   // д��λ����Ϣ
    settings.setValue("size", size()); // д����С��Ϣ
}

void MainWindow::readSettings() // ��ȡ��������
{
    QSettings settings("yafeilinux", "myMdi");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    move(pos);
    resize(size);
}

void MainWindow::showTextRowAndCol() // ��ʾ�ı����кź��к�
{
    // �����л���ڣ�����ʾ���й������ڵ�λ��
    if(activeMdiChild()){

        // ��Ϊ��ȡ���кź��кŶ��Ǵ�0��ʼ�ģ������������������˼�1
        int rowNum = activeMdiChild()->textCursor().blockNumber()+1;
        int colNum = activeMdiChild()->textCursor().columnNumber()+1;

        ui->statusBar->showMessage(tr("%1�� %2��")
                                   .arg(rowNum).arg(colNum),2000);
    }
}

void MainWindow::initWindow() // ��ʼ������
{
    setWindowTitle(codec->toUnicode("记事本"));

    // �����ڹ������ϵ��������Ҽ�ʱ�����Թرչ�����
    ui->mainToolBar->setWindowTitle(codec->toUnicode("������"));

    // �����ĵ����������ݳ������������󣬳��ֹ�����
    ui->mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    ui->statusBar->showMessage(codec->toUnicode("��ӭʹ���������ĵ��༭��"));

    QLabel *label = new QLabel(this);
    label->setFrameStyle(QFrame::Box | QFrame::Sunken);
    label->setText(
          tr("<a href=\"https://blog.csdn.net/qq_46424406?spm=1003.2020.3001.5343\">Google.com</a>"));
    label->setTextFormat(Qt::RichText); // ��ǩ�ı�Ϊ���ı�
    label->setOpenExternalLinks(true);  // ���Դ����ⲿ����
    ui->statusBar->addPermanentWidget(label);

    ui->actionNew->setStatusTip(codec->toUnicode("����һ���ļ�"));

    ui->actionOpen->setStatusTip(codec->toUnicode("����һ���Ѿ����ڵ��ļ�"));
    ui->actionSave->setStatusTip(codec->toUnicode("�����ĵ���Ӳ��"));
    ui->actionSaveAs->setStatusTip(codec->toUnicode("���µ����Ʊ����ĵ�"));
    ui->actionExit->setStatusTip(codec->toUnicode("�˳�Ӧ�ó���"));
    ui->actionUndo->setStatusTip(codec->toUnicode("������ǰ�Ĳ���"));
    ui->actionRedo->setStatusTip(codec->toUnicode("�ָ���ǰ�Ĳ���"));
    ui->actionCut->setStatusTip(codec->toUnicode("����ѡ�е����ݵ�������"));
    ui->actionCopy->setStatusTip(codec->toUnicode("����ѡ�е����ݵ�������"));
    ui->actionPaste->setStatusTip(codec->toUnicode("ճ�������������ݵ���ǰλ��"));
    ui->actionClose->setStatusTip(codec->toUnicode("�رջ����"));
    ui->actionCloseAll->setStatusTip(codec->toUnicode("�ر����д���"));
    ui->actionTile->setStatusTip(codec->toUnicode("ƽ�����д���"));
    ui->actionCascade->setStatusTip(codec->toUnicode("�������д���"));
    ui->actionNext->setStatusTip(codec->toUnicode("�������ƶ�����һ������"));
    ui->actionPrevious->setStatusTip(codec->toUnicode("�������ƶ���ǰһ������"));
    ui->actionAbout->setStatusTip(codec->toUnicode("��ʾ�������Ľ���"));

}
