#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <opencv2/imgproc/imgproc.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString m_imgFileName;

    cv::Mat m_sourceImg;
    cv::Mat m_toDisplayImg;

    QString m_vidFileName;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void DisplayImage();
    void DisplayVideo();

private slots:
    void on_openImage_clicked();

    void on_noFilter_clicked();
    void on_filter1_clicked();
    void on_filter2_clicked();
    void on_filter3_clicked();

    void on_openVideo_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
