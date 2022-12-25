#ifndef CALCULATE_H
#define CALCULATE_H

#include <QWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QButtonGroup>
#include <QString>
class Calculate : public QWidget
{
    Q_OBJECT
public:
    explicit Calculate(QWidget *parent = nullptr);

    double SH;
    double kn;

    //Masuda
    double Masuda_kn_group[60];
    double Masuda_SH_group[60];
    double Masuda_kn;
    double Masuda_SH;
    double Masuda_N = 4;
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
    double Hybrid_alpha = 0.5; //0 - 1
    double Hybrid_Beta = 5;    //-5 - 30

    QCheckBox *modelbox1;
    QCheckBox *modelbox2;
    QCheckBox *modelbox3;
    QCheckBox *modelbox4;
    QCheckBox *modelbox5;

    QSpinBox *spinbox;

    void calculate(QString);

    int model = 0;


    QButtonGroup *group;


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


    QString label_str = "font-family: 'Microsoft YaHei';"
                        "font-size: 18px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        "color: #4B0082;";

    QString lineedit_str = "QLineEdit{font: large;"
                           "Times NewRoman;"
                           "font-size:20px;"
                           "color:black;"
                           "border:4px solid #4169E1;"
                           "border-radius:5px;}";

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
private:
    QGroupBox *createFirstGroup();

private slots:

signals:

};

#endif // CALCULATE_H
