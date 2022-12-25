#ifndef THEAPP_H
#define THEAPP_H

#include <QMainWindow>
#include <QAxObject>
#include <QUrl>
#include <QDesktopServices>
#include <QTextEdit>
#include <QTime>
#include <QComboBox>
#include <QColorDialog>
#include <algorithm>
#include <QtMath>
#include "calculate.h"
#include "chartview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class theapp; }
QT_END_NAMESPACE

class theapp : public QMainWindow
{
    Q_OBJECT

public:
    theapp(QWidget *parent = nullptr);
    ~theapp();

    int input_file_num = 0;

    double input_SH[60];
    double input_kn[60];

    double a_fit3 = 0;
    double b_fit3 = 0;
    double c_fit3 = 0;
    double d_fit3 = 0;

    int N = 0;
    double y_sum = 0;
    double y_ave;
    double xy_sum = 0;
    double x2y_sum = 0;
    double x3y_sum = 0;
    double x_sum = 0;
    double x2_sum = 0;
    double x3_sum = 0;
    double x4_sum = 0;
    double x5_sum = 0;
    double x6_sum = 0;


    int fit_count = 0;
    //Masuda
    double Masuda_min_r2 = 999;
    double Masuda_count_N = 0;
    double Masuda_min_N = 0;
    double Masuda_func(double Masuda_N_func , double Masuda_SH_func[] , double Masuda_kn_func[]);
    //Patchy
    double Patchy_min_r2 = 999;
    double Patchy_count_N = 0;
    double Patchy_min_N = 0;
    double Patchy_func(double Patchy_N_func , double Patchy_SH_func[] , double Patchy_kn_func[]);
    //Hybrid
    double Hybrid_min_r2 = 999;
    double Hybrid_count_alpha = 0; //0 ~ 1
    double Hybrid_count_beta = -5.0; //-5 ~ 30
    double Hybrid_min_alpha = 0;
    double Hybrid_min_beta = 0;
    double Hybrid_func(double Hybrid_alpha_func , double Hybrid_beta_func , double Hybrid_SH_func[] , double Hybrid_kn_func[]);


    double RMSE_Masuda = 0;
    double RMSE_Patchy = 0;
    double RMSE_GC = 0;
    double RMSE_PF = 0;
    double RMSE_Hybrid = 0;

    int RMSE_min_count = 0;

    QList<double> RMSE_list;

    QTextEdit *analyse_result;
    QCheckBox *enforce_show;


    //Masuda
    double Masuda_kn_group[60];
    double Masuda_SH_group[60];
    double Masuda_kn;
    double Masuda_SH;
    double Masuda_N = 3.5;
    //Patchy
    double Patchy_kr_group[60];
    double Patchy_SH_group[60];
    double Patchy_kr;
    double Patchy_SH;
    double Patchy_N = 2;


    //G-C
    double GC_kn_group[60];
    double GC_SH_group[60];
    double GC_kn;
    double GC_SH;
    //P-F
    double PF_kn_group[60];
    double PF_SH_group[60];
    double PF_kn;
    double PF_SH;

    //Hybrid
    double Hybrid_kn_group[60];
    double Hybrid_SH_group[60];
    double Hybrid_kn;
    double Hybrid_SH;
    double Hybrid_alpha = 0.5;
    double Hybrid_Beta = 5;


    Calculate *calwidget;
    QTableWidget *tablewidget1 = new QTableWidget();
    QTableWidget *tablewidget2 = new QTableWidget();
    QTableWidget *tablewidget3 = new QTableWidget();
    int cross_count = 0;
    int mark_y_count = 0;

    chartview *m_LineChartview = new chartview(this);
    QTextEdit *status_textedit;
    QTime currentTime;
    QString currentTime_text;
    QString temp_text;


    QString output_filepath;
    QDateTime currentDateTime;


    QPushButton *FirstBox_starbtn;
    QPushButton *FirstBox_fittingbtn;
    QPushButton *FirstBox_changebtn;
    QPushButton *FirstBox_backbtn;

    QGroupBox *createFirstBox();
    QGroupBox *FirstBox;
    QButtonGroup *Firstgroup;


    QGroupBox *createSixthBox();
    QGroupBox *SixthBox;
    QGroupBox *create7thBox();
    QGroupBox *_7thBox;
    QGroupBox *create8thBox();
    QGroupBox *_8thBox;

    QLineEdit *Masuda_N_edit;
    QLineEdit *Patchy_N_edit;
    QLineEdit *Hybrid_alpha_edit;
    QLineEdit *Hybrid_Beta_edit;

    QCheckBox *modelbox0;
    QCheckBox *modelbox1;
    QCheckBox *modelbox2;
    QCheckBox *modelbox3;
    QCheckBox *modelbox4;
    QCheckBox *modelbox5;

    QPushButton *SecondBox_starbtn;
    QPushButton *SecondBox_combined_show_btn;
    QPushButton *SecondBox_combinebtn;
    QGroupBox *createSecondBox();
    QGroupBox *createThirdBox();
    QGroupBox *SecondBox;
    QGroupBox *ThirdBox;
    QButtonGroup *Secondgroup;
    QButtonGroup *Thirdgroup;

    QSpinBox *combinebox1;
    QSpinBox *combinebox2;

    int combine_num1 = 0;
    int combine_num2 = 1;

    QCheckBox *input_box0;
    QCheckBox *input_box1;
    QCheckBox *input_box2;
    QCheckBox *input_box3;

    QCheckBox *combined_box0;
    QCheckBox *combined_box1;
    QCheckBox *combined_box2;

    QString input_box0_name = "Original Data 1";
    QString input_box1_name = "Original Data 2";
    QString input_box2_name = "Original Data 3";
    QString input_box3_name = "Original Data 4";

    void fitting_calculate();

    QGroupBox *createFourthBox();
    QGroupBox *createFifthBox();
    QGroupBox *FourthBox;
    QGroupBox *FifthBox;

    QPushButton *savebtn1;
    QPushButton *savebtn2;

    QPushButton *setbackbtn1;
    QPushButton *setbackbtn2;

    //FourthBox
    QString strText_x_axis = QString::fromStdWString((L"<font style = 'font-size:20px; "
                                               "font-weight:bold;"
                                               "font-family: Arial;'>"
                                               "Saturation"));

    QLineEdit *x_name;
    QString x_name_text = "Saturation";
    QLineEdit *x_range1;
    QString x_range1_text = "0";
    QLineEdit *x_range2;
    QString x_range2_text = "0.5";

    QString strText_y_axis = QString::fromStdWString((L"<font style = 'font-size:20px; "
                                                      "font-weight:bold;"
                                                      "font-family: Arial;'>"
                                                      "Permeability"));

    QLineEdit *y_name;
    QString y_name_text = "Permeability";
    QLineEdit *y_range1;
    QString y_range1_text = "0";
    QLineEdit *y_range2;
    QString y_range2_text = "1";

    QLineEdit *title;
    QString Chartname = "Model Coordinate System";
    QString Chartname1 = "Data Coordinate System";
    QString strText = QString::fromStdWString((L"<font style = 'font-size:25px; "
                                               "font-weight:bold;"
                                               "font-family: Arial;'>"
                                               "Model "
                                               "</font>"
                                               "<font style = 'color:#2C5DFF;"
                                               "font-size:25px; "
                                               "font-weight:bold;"
                                               "font-family: Arial;'>"
                                               "Coordinate "
                                               "</font>"
                                               "<font style = 'font-size:25px;"
                                               "font-weight:bold;"
                                               "font-family: Arial;'>"
                                               "System"));

    QString strText1 = QString::fromStdWString((L"<font style = 'font-size:25px; "
                                                "font-weight:bold;"
                                                "font-family: Arial;'>"
                                                "Data Coordinate System"));
    QString title_text = Chartname;  //Model Axis

    QComboBox *legendBox;
    QLineEdit *legendedit;
    QString item_text0 = "Original Data";  //Original Data
    QString item_text1 = "Tokyo model";  //Masuda
    QString item_text2 = "Patchy model";  //Patchy
    QString item_text3 = "G-C model";  //G-C
    QString item_text4 = "P-F model";  //P-F
    QString item_text5 = "Hybrid model";  //Hybrid

    QList<QString>item_text_list;
    QPushButton *legend_savebtn;

    QColor chartcolor = Qt::white;
    QColor point_color0 = Qt::black;
    QColor line_color1 = QColor(255,140,0);
    QColor line_color2 = QColor(60,179,113);
    QColor line_color3 = QColor(72,61,139);
    QColor line_color4 = QColor(148,0,211);
    QColor line_color5 = QColor(30,144,255);
    QComboBox *datacolorBox;
    QList<QColor>line_color_list;
    QPushButton *color_savebtn1;
    QSpinBox *sizebox;
    QPushButton *size_savebtn;
    int size = 4;
    int size_point = 8;
    QPushButton *color_savebtn2;

    //FifthBox
    QLineEdit *x_name_;
    QString x_name_text_ = "Saturation";
    QString x_style_text_ = "Saturation";
    QLineEdit *x_range1_;
    QString x_range1_text_ = "0";
    QLineEdit *x_range2_;
    QString x_range2_text_ = "1";
    QString strText_x_axis1 = QString::fromStdWString((L"<font style = 'font-size:20px; "
                                                       "font-weight:bold;"
                                                       "font-family: Arial;'>"
                                                       "Saturation"));


    QLineEdit *y_name_;
    QString y_name_text_ = "Permeability";
    QLineEdit *y_range1_;
    QString y_range1_text_ = "0";
    QLineEdit *y_range2_;
    QString y_range2_text_ = "1";
    QString strText_y_axis1 = QString::fromStdWString((L"<font style = 'font-size:20px; "
                                                       "font-weight:bold;"
                                                       "font-family: Arial;'>"
                                                       "Permeability"));

    QLineEdit *title_;
    QString title_text_ = Chartname1;  //Data Axis

    QComboBox *legendBox_;
    QLineEdit *legendedit_;
    QString item_text0_ = "Original Data 1";
    QString item_text1_ = "Original Data 2";
    QString item_text2_ = "Original Data 3";
    QString item_text3_ = "Original Data 4";
    QString item_text4_ = "Combined Data 1";
    QString item_text5_ = "Combined Data 2";
    QString item_text6_ = "Combined Data 3";
    QList<QString>item_text_list_;
    QPushButton *legend_savebtn_;

    QColor chartcolor_ = Qt::white;
    QColor point_color0_ = QColor(0,191,255);
    QColor point_color1_ = QColor(255,165,0);
    QColor point_color2_ = QColor(60,179,113);
    QColor point_color3_ = QColor(0,139,139);
    QColor point_color4_ = QColor(255,20,147);
    QColor point_color5_ = QColor(123,104,238);
    QColor point_color6_ = QColor(139,0,0);
    QComboBox *datacolorBox_;
    QList<QColor>point_color_list_;
    QPushButton *color_savebtn1_;
    QSpinBox *sizebox_;
    QPushButton *size_savebtn_;
    int size_ = 8;
    QPushButton *color_savebtn2_;


    QString excel_str = "file:///C:/ALHPA MODEL/excel_example.xlsx";

    QString barstyle = "QMenuBar{background-color:rgb(244,232,210);"
                       "border: 2px solid gray;"
                       "border-style: inset;}"
                       "QMenuBar::selected{background-color:rgb(244,232,210);}"
                       "QMenuBar::item{font-size:12px;"
                       "font-family:Microsoft YaHei;"
                       "color:black;}";

    QString label_str = "font-family: 'Microsoft YaHei';"
                        "font-size: 18px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        "color: #4B0082;";

    QString label_str_small = "font-family: 'Microsoft YaHei';"
                        "font-size: 14px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        "color: #4B0082;";

    QString btnstyle = "QPushButton{color:black;"
                       "background-color:rgb(0,191,255);"
                       "border-radius: 5px;  "
                       "border: 4px rgb(0,0,128);"
                       "border-style: outset;}"
                       "QPushButton:pressed{background-color:rgb(255,255,0);"
                       "border-style: inset; }"
                       "QPushButton{font-family:Microsoft YaHei;"
                       "font-weight: bold;"
                       "font-size:18px};";

    QString btnstyle_small = "QPushButton{color:black;"
                       "background-color:rgb(0,191,255);"
                       "border-radius: 5px;  "
                       "border: 4px rgb(0,0,128);"
                       "border-style: outset;}"
                       "QPushButton:pressed{background-color:rgb(255,255,0);"
                       "border-style: inset; }"
                       "QPushButton{font-family:Microsoft YaHei;"
                       "font-weight: bold;"
                       "font-size:15px};";


    QString groupstyle = "QGroupBox{"
                         "border: 4px solid #4169E1;"
                         "border-radius: 3px;"
                         "margin-top: 1ex;"
                         "font-family:Microsoft YaHei;"
                         "font:bold;"
                         "font-size:16px;"
                         "}"
                         "QGroupBox::title{"
                         "subcontrol-origin: margin;"
                         "subcontrol-position: top center;"
                         "padding: 0 3px;"
                         "}";

    QString checkboxstyle = "QCheckBox{"
                            "font-family:Microsoft YaHei;"
                            "font-size:16px;"
                            "spacing: 5px;"
                            "}";

    QString lineedit_str = "QLineEdit{font: large;"
                           "Times NewRoman;"
                           "font-size:20px;"
                           "color:black;"
                           "border:4px solid #4169E1;"
                           "border-radius:5px;}";





private:
    Ui::theapp *ui;
};
#endif // THEAPP_H
