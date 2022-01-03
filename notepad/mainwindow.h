#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MdiChild;
class QMdiSubWindow;
class QSignalMapper;
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionNew_triggered(); // �½��ļ��˵�
    void updateMenus(); // ���²˵�
    MdiChild *createMdiChild(); // �����Ӵ���
    void setActiveSubWindow(QWidget *window); // ���û�Ӵ���

    void on_actionOpen_triggered(); // �����ļ��˵�

    void updateWindowMenu(); // ���´��ڲ˵�

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionClose_triggered();

    void on_actionCloseAll_triggered();

    void on_actionTile_triggered();

    void on_actionCascade_triggered();

    void on_actionNext_triggered();

    void on_actionPrevious_triggered();

    void on_actionAbout_triggered();

//    void on_actionAboutQt_triggered();

    void on_actionExit_triggered();

    void showTextRowAndCol(); // ��ʾ�ı����кź��к�

private:
    Ui::MainWindow *ui;
    QAction *actionSeparator; // �ָ���
    MdiChild *activeMdiChild(); // �����
    QMdiSubWindow *findMdiChild(const QString &fileName);// �����Ӵ���

    QSignalMapper *windowMapper; // �ź�ӳ����

    void readSettings();  // ��ȡ��������
    void writeSettings(); // д�봰������


    void initWindow(); // ��ʼ������

protected:
    void closeEvent(QCloseEvent *event);  // �ر��¼�
};

#endif // MAINWINDOW_H
