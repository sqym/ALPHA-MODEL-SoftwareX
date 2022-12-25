#ifndef CHARTVIEW_H
#define CHARTVIEW_H
#include <QWidget>
#include <QtCharts>
#include <QChartView>
#include <QtWidgets/QGraphicsView>
#include <QPoint>
#include <QToolTip>
#include <QLabel>
#include <QPainter>
#include <QRubberBand>

QT_CHARTS_USE_NAMESPACE
class chartview : public QChartView
{
    Q_OBJECT
public:
    explicit chartview(QWidget *parent = nullptr);

    int model_type = 0;
    int current_chart = 0;

    double fitting3_SH[60];
    double fitting3_kn[60];

    double input_SH[60];
    double input_kn[60];

    double input_SH0[60];
    double input_kn0[60];

    double input_SH1[60];
    double input_kn1[60];

    double input_SH2[60];
    double input_kn2[60];

    double input_SH3[60];
    double input_kn3[60];

    QList<double*>input_SH_list;
    QList<double*>input_kn_list;
    double combine_SH0[120];
    double combine_kn0[120];

    double combine_SH1[120];
    double combine_kn1[120];

    double combine_SH2[120];
    double combine_kn2[120];

    int count_num = 0;
    int filled_num = 0;
    QList<double*>combine_SH_list;
    QList<double*>combine_kn_list;

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
    double Hybrid_alpha = 0.35; //0 - 1
    double Hybrid_Beta = 5;    //-5 - 30

    int click_trigger = 0;
    double point_x;
    double point_y;

    int zoom_count = 0;    

    double zoom_point1_x;
    double zoom_point1_y;
    double zoom_point2_x;
    double zoom_point2_y;

    double rubberBand_start_x;
    double rubberBand_start_y;

    QRubberBand *rubberBand;
    QPoint origin;


    QString mouse_X = "X: ";
    QString mouse_Y = "Y: ";

    QString mouse_move_X = "X: %1";
    QString mouse_move_Y = "Y: %1";


    int Axis_trigger = 0;

    QValueAxis *m_AxisY = new QValueAxis();
    QValueAxis *m_AxisX = new QValueAxis();

    QValueAxis *m_AxisY1 = new QValueAxis();
    QValueAxis *m_AxisX1 = new QValueAxis();

    void attach_Axis();
    void attach_log_Axis();


    QPen mark_Series;

    QLineSeries *mark_Series1 = new QLineSeries();
    QLineSeries *mark_Series2 = new QLineSeries();
    QLineSeries *mark_Series3 = new QLineSeries();
    QLineSeries *mark_Series4 = new QLineSeries();
    QLineSeries *mark_Series5 = new QLineSeries();
    QLineSeries *mark_Series6 = new QLineSeries();

    QLineSeries *mark_Series1_ = new QLineSeries();
    QLineSeries *mark_Series2_ = new QLineSeries();
    QLineSeries *mark_Series3_ = new QLineSeries();
    QLineSeries *mark_Series4_ = new QLineSeries();
    QLineSeries *mark_Series5_ = new QLineSeries();
    QLineSeries *mark_Series6_ = new QLineSeries();

    QLineSeries *crossx_Series = new QLineSeries();
    QLineSeries *crossy_Series = new QLineSeries();
    QLineSeries *crossx__Series = new QLineSeries();
    QLineSeries *crossy__Series = new QLineSeries();
    int cross_trigger = 0;

    QList<QLineSeries*>mark_Series_list;
    QList<QLineSeries*>mark_Series_list_;
    int list_count = 0;
    int list_count_ = 0;


    QLineSeries *fitting_Series3 = new QLineSeries();
    QPen fitting_pen;

    QPen m_Series0_pen;
    QScatterSeries *m_Series0 = new QScatterSeries();

    QPen m_Series1_pen;
    QLineSeries *m_Series1 = new QLineSeries();

    QPen m_Series2_pen;
    QLineSeries *m_Series2 = new QLineSeries();

    QPen m_Series3_pen;
    QLineSeries *m_Series3 = new QLineSeries();

    QPen m_Series4_pen;
    QLineSeries *m_Series4 = new QLineSeries();

    QPen m_Series5_pen;
    QLineSeries *m_Series5 = new QLineSeries();

    QScatterSeries *input_Series0 = new QScatterSeries();
    QScatterSeries *input_Series1 = new QScatterSeries();
    QScatterSeries *input_Series2 = new QScatterSeries();
    QScatterSeries *input_Series3 = new QScatterSeries();
    QScatterSeries *input_Series4 = new QScatterSeries();
    QScatterSeries *input_Series5 = new QScatterSeries();
    QScatterSeries *input_Series6 = new QScatterSeries();
    QScatterSeries *input_Series7 = new QScatterSeries();

    QScatterSeries *combine_Series0 = new QScatterSeries();
    QScatterSeries *combine_Series1 = new QScatterSeries();
    QScatterSeries *combine_Series2 = new QScatterSeries();

    QChart *m_LineChart = new QChart();
    QChart *m_LineChart1 = new QChart();

    void setLineChartMargins(QChart *m_LineChart, int margin);
    void addPointToChart_original_ver(QScatterSeries *targetSeries, double x[],double y[]);
    void addPointToChart_model_ver(QLineSeries *targetSeries, double x[],double y[]);
    void addPointToChart_combine_ver(QScatterSeries *targetSeries, double x[],double y[]);
    void addFittingCurveToChart(QLineSeries *targetSeries, double x[],double y[]);

    void calculate();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


    int tooltip_trigger = 0;
    QToolTip *tip;

    int click_point_trigger = 0;
    double click_point_x;
    double click_point_y;

    int click_point_agreement = 0;

    QLabel *showlabel1 = new QLabel(this);
    QLabel *showlabel2 = new QLabel(this);
    QLabel *showlabel3 = new QLabel(this);
    QLabel *showlabel4 = new QLabel(this);
    QLabel *showlabel5 = new QLabel(this);
    QLabel *showlabel6 = new QLabel(this);

    QLabel *colorlabel1 = new QLabel(this);
    QLabel *colorlabel2 = new QLabel(this);
    QLabel *colorlabel3 = new QLabel(this);
    QLabel *colorlabel4 = new QLabel(this);
    QLabel *colorlabel5 = new QLabel(this);
    QLabel *colorlabel6 = new QLabel(this);

    QPalette pe1;
    QPalette pe2;
    QPalette pe3;
    QPalette pe4;
    QPalette pe5;
    QPalette pe6;

    QLabel *showlabel7 = new QLabel(this);
    QLabel *showlabel8 = new QLabel(this);
    QLabel *showlabel9 = new QLabel(this);
    QLabel *showlabel10 = new QLabel(this);
    QLabel *showlabel11 = new QLabel(this);
    QLabel *showlabel12 = new QLabel(this);
    QLabel *showlabel13 = new QLabel(this);

    QLabel *colorlabel7 = new QLabel(this);
    QLabel *colorlabel8 = new QLabel(this);
    QLabel *colorlabel9 = new QLabel(this);
    QLabel *colorlabel10 = new QLabel(this);
    QLabel *colorlabel11 = new QLabel(this);
    QLabel *colorlabel12 = new QLabel(this);
    QLabel *colorlabel13 = new QLabel(this);

    QPalette pe7;
    QPalette pe8;
    QPalette pe9;
    QPalette pe10;
    QPalette pe11;
    QPalette pe12;
    QPalette pe13;

    QString label_str1 = "font-family: 'Microsoft YaHei';"
                        "font-size: 22px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        "color: #000000;";
    QString label_str2 = "font-family: 'Microsoft YaHei';"
                        "font-size: 18px;"
                        "font-style: normal;"
                        "font-weight: bold;"
                        "color: #000000;";


private slots:

    void tooltip(QPointF point, bool state);

private:
    QGraphicsSimpleTextItem *m_chartvalue_X;
    QGraphicsSimpleTextItem *m_chartvalue_Y;

    QGraphicsSimpleTextItem *m_chartvalue_X1;
    QGraphicsSimpleTextItem *m_chartvalue_Y1;

    QGraphicsSimpleTextItem *m_coordX;
    QGraphicsSimpleTextItem *m_coordY;

    QGraphicsSimpleTextItem *m_coordX1;
    QGraphicsSimpleTextItem *m_coordY1;


signals:

};

#endif // CHARTVIEW_H
