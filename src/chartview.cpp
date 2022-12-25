#include "chartview.h"

chartview::chartview(QWidget *parent) : QChartView(parent),
    m_chartvalue_X(0),
    m_chartvalue_Y(0)
{

    rubberBand = new QRubberBand(QRubberBand::Rectangle,this);

        for(int i=0;i<60;i++)
        {

            fitting3_SH[i] = 0;
            fitting3_kn[i] = 0;

            input_SH[i] = 0;
            input_kn[i] = 0;

            input_SH0[i] = 0;
            input_kn0[i] = 0;

            input_SH1[i] = 0;
            input_kn1[i] = 0;

            input_SH2[i] = 0;
            input_kn2[i] = 0;

            input_SH3[i] = 0;
            input_kn3[i] = 0;

            Masuda_SH_group[i]=0;
            Masuda_kn_group[i]=0;

            Patchy_SH_group[i]=0;
            Patchy_kr_group[i]=0;

            Hybrid_SH_group[i]=0;
            Hybrid_kn_group[i]=0;

            GC_SH_group[i]=0;
            GC_kn_group[i]=0;

            PF_SH_group[i]=0;
            PF_kn_group[i]=0;
        }
        for(int i=0;i<120;i++)
        {
            combine_SH0[i] = 0;
            combine_kn0[i] = 0;

            combine_SH1[i] = 0;
            combine_kn1[i] = 0;

            combine_SH2[i] = 0;
            combine_kn2[i] = 0;
        }

        showlabel1->setText("Original Data");
        showlabel1->setGeometry(760,93,200,50);
        showlabel1->setStyleSheet(label_str1);

        colorlabel1->setGeometry(727,110,20,20);

        pe1.setColor(QPalette::Background,Qt::black);
        colorlabel1->setPalette(pe1);
        colorlabel1->setAutoFillBackground(true);


        showlabel2->setText("Tokyo model");
        showlabel2->setGeometry(760,123,200,50);
        showlabel2->setStyleSheet(label_str1);

        colorlabel2->setGeometry(727,140,20,20);
        pe2.setColor(QPalette::Background,QColor(255,140,0));
        colorlabel2->setPalette(pe2);
        colorlabel2->setAutoFillBackground(true);

        showlabel3->setText("Patchy model");
        showlabel3->setGeometry(760,153,200,50);
        showlabel3->setStyleSheet(label_str1);

        colorlabel3->setGeometry(727,170,20,20);
        pe3.setColor(QPalette::Background,QColor(60,179,113));
        colorlabel3->setPalette(pe3);
        colorlabel3->setAutoFillBackground(true);

        showlabel4->setText("G-C model");
        showlabel4->setGeometry(760,183,200,50);
        showlabel4->setStyleSheet(label_str1);

        colorlabel4->setGeometry(727,200,20,20);
        pe4.setColor(QPalette::Background,QColor(72,61,139));
        colorlabel4->setPalette(pe4);
        colorlabel4->setAutoFillBackground(true);

        showlabel5->setText("P-F model");
        showlabel5->setGeometry(760,213,200,50);
        showlabel5->setStyleSheet(label_str1);

        colorlabel5->setGeometry(727,230,20,20);
        pe5.setColor(QPalette::Background,QColor(148,0,211));
        colorlabel5->setPalette(pe5);
        colorlabel5->setAutoFillBackground(true);

        showlabel6->setText("Hybrid model");
        showlabel6->setGeometry(760,243,200,50);
        showlabel6->setStyleSheet(label_str1);

        colorlabel6->setGeometry(727,260,20,20);
        pe6.setColor(QPalette::Background,QColor(30,144,255));
        colorlabel6->setPalette(pe6);
        colorlabel6->setAutoFillBackground(true);

        showlabel7->setText("Original Data 1");
        showlabel7->setGeometry(810,102,200,30);
        showlabel7->setStyleSheet(label_str2);
        showlabel7->hide();


        colorlabel7->setGeometry(792,110,15,15);
        pe7.setColor(QPalette::Background,QColor(0,191,255));
        colorlabel7->setPalette(pe7);
        colorlabel7->setAutoFillBackground(true);
        colorlabel7->hide();

        showlabel8->setText("Original Data 2");
        showlabel8->setGeometry(810,122,200,30);
        showlabel8->setStyleSheet(label_str2);
        showlabel8->hide();

        colorlabel8->setGeometry(792,130,15,15);
        pe8.setColor(QPalette::Background,QColor(255,165,0));
        colorlabel8->setPalette(pe8);
        colorlabel8->setAutoFillBackground(true);
        colorlabel8->hide();

        showlabel9->setText("Original Data 3");
        showlabel9->setGeometry(810,142,200,30);
        showlabel9->setStyleSheet(label_str2);
        showlabel9->hide();


        colorlabel9->setGeometry(792,150,15,15);
        pe9.setColor(QPalette::Background,QColor(60,179,113));
        colorlabel9->setPalette(pe9);
        colorlabel9->setAutoFillBackground(true);
        colorlabel9->hide();

        showlabel10->setText("Original Data 4");
        showlabel10->setGeometry(810,162,200,30);
        showlabel10->setStyleSheet(label_str2);
        showlabel10->hide();

        colorlabel10->setGeometry(792,170,15,15);
        pe10.setColor(QPalette::Background,QColor(0,139,139));
        colorlabel10->setPalette(pe10);
        colorlabel10->setAutoFillBackground(true);
        colorlabel10->hide();

        showlabel11->setText("Combined Data 1");
        showlabel11->setGeometry(810,182,200,30);
        showlabel11->setStyleSheet(label_str2);
        showlabel11->hide();

        colorlabel11->setGeometry(792,190,15,15);
        pe11.setColor(QPalette::Background,QColor(255,20,147));
        colorlabel11->setPalette(pe11);
        colorlabel11->setAutoFillBackground(true);
        colorlabel11->hide();

        showlabel12->setText("Combined Data 2");
        showlabel12->setGeometry(810,202,200,30);
        showlabel12->setStyleSheet(label_str2);
        showlabel12->hide();

        colorlabel12->setGeometry(792,210,15,15);
        pe12.setColor(QPalette::Background,QColor(123,104,238));
        colorlabel12->setPalette(pe12);
        colorlabel12->setAutoFillBackground(true);
        colorlabel12->hide();

        showlabel13->setText("Combined Data 3");
        showlabel13->setGeometry(810,222,200,30);
        showlabel13->setStyleSheet(label_str2);
        showlabel13->hide();

        colorlabel13->setGeometry(792,230,15,15);
        pe13.setColor(QPalette::Background,QColor(139,0,0));
        colorlabel13->setPalette(pe13);
        colorlabel13->setAutoFillBackground(true);
        colorlabel13->hide();


      input_SH_list.append(input_SH0);
      input_kn_list.append(input_kn0);

      input_SH_list.append(input_SH1);
      input_kn_list.append(input_kn1);

      input_SH_list.append(input_SH2);
      input_kn_list.append(input_kn2);

      input_SH_list.append(input_SH3);
      input_kn_list.append(input_kn3);

      combine_SH_list.append(combine_SH0);
      combine_kn_list.append(combine_kn0);

      combine_SH_list.append(combine_SH1);
      combine_kn_list.append(combine_kn1);

      combine_SH_list.append(combine_SH2);
      combine_kn_list.append(combine_kn2);


      this->setMouseTracking(true);

      m_LineChart->setAcceptHoverEvents(true);
      m_LineChart1->setAcceptHoverEvents(true);


      m_chartvalue_X = new QGraphicsSimpleTextItem(m_LineChart);
      m_chartvalue_X1 = new QGraphicsSimpleTextItem(m_LineChart1);


      QFont mouse_position_Font("Arial", 12, QFont::Bold);
      m_chartvalue_X->setPos(100,740);
      m_chartvalue_X->setFont(mouse_position_Font);
      m_chartvalue_X->setText(mouse_X);


      m_chartvalue_X1->setPos(100,740);
      m_chartvalue_X1->setFont(mouse_position_Font);
      m_chartvalue_X1->setText(mouse_X);

      m_chartvalue_Y = new QGraphicsSimpleTextItem(m_LineChart);
      m_chartvalue_Y1 = new QGraphicsSimpleTextItem(m_LineChart1);


      m_chartvalue_Y->setPos(100,760);
      m_chartvalue_Y->setFont(mouse_position_Font);
      m_chartvalue_Y->setText(mouse_Y);


      m_chartvalue_Y1->setPos(100,760);
      m_chartvalue_Y1->setFont(mouse_position_Font);
      m_chartvalue_Y1->setText(mouse_Y);


      m_LineChart->setTheme(QChart::ChartThemeBlueNcs);
      m_LineChart1->setTheme(QChart::ChartThemeBlueNcs);

      m_LineChart->addSeries(m_Series0); m_LineChart1->addSeries(input_Series0);
      m_LineChart->addSeries(m_Series1); m_LineChart1->addSeries(input_Series1);
      m_LineChart->addSeries(m_Series2); m_LineChart1->addSeries(input_Series2);
      m_LineChart->addSeries(m_Series3); m_LineChart1->addSeries(input_Series3);
      m_LineChart->addSeries(m_Series4);
      m_LineChart->addSeries(m_Series5);

      m_LineChart->addSeries(fitting_Series3);

      m_LineChart1->addSeries(combine_Series0);
      m_LineChart1->addSeries(combine_Series1);
      m_LineChart1->addSeries(combine_Series2);


      m_LineChart->addSeries(mark_Series1);
      m_LineChart->addSeries(mark_Series2);
      m_LineChart->addSeries(mark_Series3);
      m_LineChart->addSeries(mark_Series4);
      m_LineChart->addSeries(mark_Series5);
      m_LineChart->addSeries(mark_Series6);

      m_LineChart1->addSeries(mark_Series1_);
      m_LineChart1->addSeries(mark_Series2_);
      m_LineChart1->addSeries(mark_Series3_);
      m_LineChart1->addSeries(mark_Series4_);
      m_LineChart1->addSeries(mark_Series5_);
      m_LineChart1->addSeries(mark_Series6_);

      m_LineChart->addSeries(crossx_Series);
      m_LineChart->addSeries(crossy_Series);

      m_LineChart1->addSeries(crossx__Series);
      m_LineChart1->addSeries(crossy__Series);



      QFont XYCount_Font("Arial", 15, QFont::Bold);
      m_AxisX->setLabelsFont(XYCount_Font);
      m_AxisX1->setLabelsFont(XYCount_Font);
      m_AxisY->setLabelsFont(XYCount_Font);
      m_AxisY1->setLabelsFont(XYCount_Font);


      m_AxisX->setTickCount(10);
      m_AxisX1->setTickCount(10);

      m_AxisY->setTickCount(10);
      m_AxisY1->setTickCount(10);


      m_AxisX->setRange(0,0.45);
      m_AxisX1->setRange(0,1);

      m_AxisY->setRange(0,1);
      m_AxisY1->setRange(0,1);

      m_LineChart->addAxis(m_AxisX, Qt::AlignBottom);
      m_LineChart->addAxis(m_AxisY, Qt::AlignLeft);

      m_LineChart1->addAxis(m_AxisX1, Qt::AlignBottom);
      m_LineChart1->addAxis(m_AxisY1, Qt::AlignLeft);


      QString strText_x_axis = QString::fromStdWString((L"<font style = 'font-size:24px; "
                                                 "font-weight:bold;"
                                                 "font-family: Arial;'>"
                                                 "Saturation"));

      QString strText_x_axis1 = QString::fromStdWString((L"<font style = 'font-size:24px; "
                                                         "font-weight:bold;"
                                                         "font-family: Arial;'>"
                                                         "Saturation"));
      m_AxisX->setTitleText(strText_x_axis);
      m_AxisX1->setTitleText(strText_x_axis1);

      QColor colorX = QColor(192,192,192);

      m_AxisX->setGridLinePen(QPen(colorX,2));
      m_AxisX->setLinePen(QPen(colorX,3));

      m_AxisX1->setGridLinePen(QPen(colorX,2));
      m_AxisX1->setLinePen(QPen(colorX,3));

      QString strText_y_axis = QString::fromStdWString((L"<font style = 'font-size:24px; "
                                                        "font-weight:bold;"
                                                        "font-family: Arial;'>"
                                                        "Permeability"));

      QString strText_y_axis1 = QString::fromStdWString((L"<font style = 'font-size:24px; "
                                                         "font-weight:bold;"
                                                         "font-family: Arial;'>"
                                                         "Permeability"));
      m_AxisY->setTitleText(strText_y_axis);
      m_AxisY1->setTitleText(strText_y_axis1);

      QColor colorY = QColor(192,192,192);
      m_AxisY->setGridLinePen(QPen(colorY,2));
      m_AxisY->setLinePen(QPen(colorY,3));

      m_AxisY1->setGridLinePen(QPen(colorY,2));
      m_AxisY1->setLinePen(QPen(colorY,3));

      m_AxisY->setMinorGridLineVisible(true);
      m_AxisY->setMinorTickCount(5);

      m_AxisY1->setMinorGridLineVisible(true);
      m_AxisY1->setMinorTickCount(5);

      fitting_pen.setColor(Qt::black);
      fitting_pen.setWidth(4);
      fitting_pen.setCapStyle(Qt::RoundCap);
      fitting_pen.setStyle(Qt::SolidLine);
      fitting_Series3->setName("Cubic polynomial fitting");
      fitting_Series3->setPen(fitting_pen);
      fitting_Series3->hide();

      m_Series0->setName("Original Data");
      m_Series0->setMarkerSize(8);
      m_Series0->setBrush(Qt::black);
      m_Series0->setBorderColor(Qt::black);

      m_Series1_pen.setColor(QColor(255,140,0));
      m_Series1_pen.setStyle(Qt::SolidLine);
      m_Series1_pen.setWidth(4);
      m_Series1_pen.setCapStyle(Qt::RoundCap);
      m_Series1_pen.setJoinStyle(Qt::RoundJoin);
      m_Series1->setPen(m_Series1_pen);
      m_Series1->setName("Tokyo model");

      m_Series2_pen.setColor(QColor(60,179,113));
      m_Series2_pen.setStyle(Qt::SolidLine);
      m_Series2_pen.setWidth(4);
      m_Series2_pen.setCapStyle(Qt::RoundCap);
      m_Series2_pen.setJoinStyle(Qt::RoundJoin);
      m_Series2->setPen(m_Series2_pen);
      m_Series2->setName("Patchy model");

      m_Series3_pen.setColor(QColor(72,61,139));
      m_Series3_pen.setStyle(Qt::DashLine);
      m_Series3_pen.setWidth(4);
      m_Series3_pen.setCapStyle(Qt::RoundCap);
      m_Series3_pen.setJoinStyle(Qt::RoundJoin);
      m_Series3->setPen(m_Series3_pen);
      m_Series3->setName("G-C model");

      m_Series4_pen.setColor(QColor(148,0,211));
      m_Series4_pen.setStyle(Qt::DashLine);
      m_Series4_pen.setWidth(4);
      m_Series4_pen.setCapStyle(Qt::RoundCap);
      m_Series4_pen.setJoinStyle(Qt::RoundJoin);
      m_Series4->setPen(m_Series4_pen);
      m_Series4->setName("P-F model");

      m_Series5_pen.setColor(QColor(30,144,255));
      m_Series5_pen.setStyle(Qt::SolidLine);
      m_Series5_pen.setWidth(4);
      m_Series5_pen.setCapStyle(Qt::RoundCap);
      m_Series5_pen.setJoinStyle(Qt::RoundJoin);
      m_Series5->setPen(m_Series5_pen);
      m_Series5->setName("Hybrid model");

      input_Series0->setName("Original Data 1");
      input_Series0->setMarkerSize(8);
      input_Series0->setBrush(QColor(0,191,255));
      input_Series0->setBorderColor(QColor(0,191,255));

      input_Series1->setName("Original Data 2");
      input_Series1->setMarkerSize(8);
      input_Series1->setBrush(QColor(255,165,0));
      input_Series1->setBorderColor(QColor(255,165,0));

      input_Series2->setName("Original Data 3");
      input_Series2->setMarkerSize(8);
      input_Series2->setBrush(QColor(60,179,113));
      input_Series2->setBorderColor(QColor(60,179,113));

      input_Series3->setName("Original Data 4");
      input_Series3->setMarkerSize(8);
      input_Series3->setBrush(QColor(0,139,139));
      input_Series3->setBorderColor(QColor(0,139,139));

      combine_Series0->setName("Combined Data 1");
      combine_Series0->setMarkerSize(8);
      QColor color_combine0 = QColor(255,20,147);
      combine_Series0->setBrush(color_combine0);
      combine_Series0->setBorderColor(color_combine0);

      combine_Series1->setName("Combined Data 2");
      combine_Series1->setMarkerSize(8);
      QColor color_combine1 = QColor(123,104,238);
      combine_Series1->setBrush(color_combine1);
      combine_Series1->setBorderColor(color_combine1);

      combine_Series2->setName("Combined Data 3");
      combine_Series2->setMarkerSize(8);
      QColor color_combine2 = QColor(139,0,0);
      combine_Series2->setBrush(color_combine2);
      combine_Series2->setBorderColor(color_combine2);

      mark_Series.setColor(Qt::red);
      mark_Series.setWidth(2);
      mark_Series.setStyle(Qt::DashLine);
      mark_Series1->setPen(mark_Series);
      mark_Series2->setPen(mark_Series);
      mark_Series3->setPen(mark_Series);
      mark_Series4->setPen(mark_Series);
      mark_Series5->setPen(mark_Series);
      mark_Series6->setPen(mark_Series);
      mark_Series1_->setPen(mark_Series);
      mark_Series2_->setPen(mark_Series);
      mark_Series3_->setPen(mark_Series);
      mark_Series4_->setPen(mark_Series);
      mark_Series5_->setPen(mark_Series);
      mark_Series6_->setPen(mark_Series);
      crossx_Series->setPen(mark_Series);
      crossy_Series->setPen(mark_Series);
      crossx__Series->setPen(mark_Series);
      crossy__Series->setPen(mark_Series);

      this->attach_Axis();
      int margin = 8;
      this->setLineChartMargins(m_LineChart,margin);
      this->setLineChartMargins(m_LineChart1,margin);

      QString Chartname = "Model Coordinate System";
      QString Chartname1 = "Data Coordinate System";

      QString strText = QString::fromStdWString((L"<font style = 'font-size:30px; "
                                                 "font-weight:bold;"
                                                 "font-family: Arial;'>"
                                                 "Model "
                                                 "</font>"
                                                 "<font style = 'color:#2C5DFF;"
                                                 "font-size:30px; "
                                                 "font-weight:bold;"
                                                 "font-family: Arial;'>"
                                                 "Coordinate "
                                                 "</font>"
                                                 "<font style = 'font-size:30px;"
                                                 "font-weight:bold;"
                                                 "font-family: Arial;'>"
                                                 "System"));

      QString strText1 = QString::fromStdWString((L"<font style = 'font-size:25px; "
                                                  "font-weight:bold;"
                                                  "font-family: Arial;'>"
                                                  "Data Coordinate System"));
      m_LineChart->setTitle(strText);
      m_LineChart1->setTitle(strText1);

      m_LineChart->setDropShadowEnabled(true);
      m_LineChart1->setDropShadowEnabled(true);

      m_LineChart->setAnimationOptions(QChart::AllAnimations);
      m_LineChart1->setAnimationOptions(QChart::AllAnimations);

      m_LineChart->setAnimationEasingCurve(QEasingCurve::InQuad);
      m_LineChart1->setAnimationEasingCurve(QEasingCurve::InQuad);

      m_LineChart->legend()->setVisible(false);
      m_LineChart1->legend()->setVisible(false);

      this->setRenderHint(QPainter::Antialiasing, true);

      this->setChart(m_LineChart);

      mark_Series_list.append(mark_Series1);
      mark_Series_list.append(mark_Series2);
      mark_Series_list.append(mark_Series3);
      mark_Series_list.append(mark_Series4);
      mark_Series_list.append(mark_Series5);
      mark_Series_list.append(mark_Series6);

      mark_Series_list_.append(mark_Series1_);
      mark_Series_list_.append(mark_Series2_);
      mark_Series_list_.append(mark_Series3_);
      mark_Series_list_.append(mark_Series4_);
      mark_Series_list_.append(mark_Series5_);
      mark_Series_list_.append(mark_Series6_);

      QObject::connect(m_Series0, &QScatterSeries::hovered, this, &chartview::tooltip);
      QObject::connect(m_Series1, &QLineSeries::hovered, this, &chartview::tooltip);
      QObject::connect(m_Series2, &QLineSeries::hovered, this, &chartview::tooltip);
      QObject::connect(m_Series3, &QLineSeries::hovered, this, &chartview::tooltip);
      QObject::connect(m_Series4, &QLineSeries::hovered, this, &chartview::tooltip);
      QObject::connect(m_Series5, &QLineSeries::hovered, this, &chartview::tooltip);

}

void chartview::calculate()
{
    for(int i=0; i<60; i++)
    {

        if(Masuda_SH_group[i] == 0 && i != 0){continue;}
        //Masuda
        Masuda_kn_group[i] = pow((1 - Masuda_SH_group[i]),Masuda_N);
        //Patchy
        Patchy_kr_group[i] = pow((1 - Patchy_SH_group[i]),3)/pow((1 + 2 * Patchy_SH_group[i]),Patchy_N);
        //GC
        GC_kn_group[i] = pow((1 - GC_SH_group[i]),2);
        //PF
        PF_kn_group[i] = (1 - pow(PF_SH_group[i],2) + 2 * pow((1 - PF_SH_group[i]),2)/log(PF_SH_group[i]));
        //Hybrid
        Hybrid_kn_group[i] = pow(GC_kn_group[i],(1/(1 + pow((Hybrid_SH_group[i]/Hybrid_alpha),Hybrid_Beta)))) * pow(PF_kn_group[i],(1 - (1/(1 + pow((Hybrid_SH_group[i]/Hybrid_alpha),Hybrid_Beta)))));
    }

}

void chartview::addPointToChart_original_ver(QScatterSeries *targetSeries, double x[] ,double y[])
{

    for(int i=0; i<60; i++)
    {
        if(x[i] == 0 && y[i] == 0){break;}
        targetSeries->append(x[i],y[i]);
    }

}
void chartview::addPointToChart_model_ver(QLineSeries *targetSeries, double x[] ,double y[])
{

    for(int i=0; i<60; i++)
    {
        if(x[i] == 0 && i!= 0){break;}
        targetSeries->append(x[i],y[i]);
    }

}
void chartview::addPointToChart_combine_ver(QScatterSeries *targetSeries, double x[] ,double y[])
{

    for(int i=0; i<120; i++)
    {
        if(x[i] == 0 && y[i] == 0){break;}
        targetSeries->append(x[i],y[i]);
    }

}
void chartview::addFittingCurveToChart(QLineSeries *targetSeries, double x[] ,double y[])
{

    for(int i=0; i<60; i++)
    {
        if(x[i] == 0 && y[i] == 0){break;}
        targetSeries->append(x[i],y[i]);
    }

}
void chartview::setLineChartMargins(QChart *chart, int margin)
{
  QMargins m_Margin;
  m_Margin.setLeft(margin);
  m_Margin.setBottom(45);
  m_Margin.setRight(margin);
  m_Margin.setTop(20);
  chart->setMargins(m_Margin);
}
void chartview::mousePressEvent(QMouseEvent *event)
{
    origin = event->pos();
    rubberBand->setGeometry(QRect(origin, QSize()));
    rubberBand->show();


    if(click_point_trigger == 1 && current_chart == 0 && click_point_agreement ==1){
    if((event->x() - m_LineChart->plotArea().left() +1 >=0) && (m_LineChart->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart->plotArea().bottom() -0.0001 <=0) && (m_LineChart->plotArea().top() - event->y() -0.0001 <=0))
        {

                click_point_x = m_LineChart->mapToValue(event->localPos()).x();
                click_point_y = m_LineChart->mapToValue(event->localPos()).y();

                click_point_trigger =0;

        }
    }}
    if(click_point_trigger == 1 && current_chart == 1 && click_point_agreement ==1){
    if((event->x() - m_LineChart1->plotArea().left() +1 >=0) && (m_LineChart1->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart1->plotArea().bottom() -0.0001 <=0) && (m_LineChart1->plotArea().top() - event->y() -0.0001 <=0))
        {

                click_point_x = m_LineChart1->mapToValue(event->localPos()).x();
                click_point_y = m_LineChart1->mapToValue(event->localPos()).y();

                click_point_trigger =0;

        }
    }}


    if(zoom_count == 1 && current_chart == 0){
    if((event->x() - m_LineChart->plotArea().left() +1 >=0) && (m_LineChart->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart->plotArea().bottom() -0.0001 <=0) && (m_LineChart->plotArea().top() - event->y() -0.0001 <=0))
        {

                zoom_point1_x = m_LineChart->mapToValue(event->localPos()).x();
                zoom_point1_y = m_LineChart->mapToValue(event->localPos()).y();

        }
    }}
    if(zoom_count == 1 && current_chart == 1){
    if((event->x() - m_LineChart1->plotArea().left() +1 >=0) && (m_LineChart1->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart1->plotArea().bottom() -0.0001 <=0) && (m_LineChart1->plotArea().top() - event->y() -0.0001 <=0))
        {

                zoom_point1_x = m_LineChart1->mapToValue(event->localPos()).x();
                zoom_point1_y = m_LineChart1->mapToValue(event->localPos()).y();

        }
    }}

    if(click_trigger == 1 && current_chart == 0){
    if((event->x() - m_LineChart->plotArea().left() +1 >=0) && (m_LineChart->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart->plotArea().bottom() -0.0001 <=0) && (m_LineChart->plotArea().top() - event->y() -0.0001 <=0))
        {

            point_x = m_LineChart->mapToValue(event->localPos()).x();
            point_y = m_LineChart->mapToValue(event->localPos()).y();

            if(list_count <= 5){
            mark_Series_list[list_count]->append(point_x,2);
            mark_Series_list[list_count]->append(point_x,-2);

            list_count ++;}else{QMessageBox::information(this,"Warning","MarkLines in Model Axis have reached upper limit.");}

        }
    }}
    if(click_trigger == 1 && current_chart == 1){
    if((event->x() - m_LineChart1->plotArea().left() +1 >=0) && (m_LineChart1->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart1->plotArea().bottom() -0.0001 <=0) && (m_LineChart1->plotArea().top() - event->y() -0.0001 <=0))
        {

            point_x = m_LineChart1->mapToValue(event->localPos()).x();
            point_y = m_LineChart1->mapToValue(event->localPos()).y();
            if(list_count_ <= 5){
            mark_Series_list_[list_count_]->append(point_x,2);
            mark_Series_list_[list_count_]->append(point_x,-2);

            list_count_ ++;}else{QMessageBox::information(this,"Warning","MarkLines in Data Axis have reached upper limit.");}

        }
    }}


}
void chartview::mouseMoveEvent(QMouseEvent *event)
{
      rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
    if((event->x() - m_LineChart->plotArea().left() +1 >=0) && (m_LineChart->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart->plotArea().bottom() -0.0001 <=0) && (m_LineChart->plotArea().top() - event->y() -0.0001 <=0))
        {

            if(cross_trigger == 1 && current_chart == 0){
            crossx_Series->clear();
            crossy_Series->clear();
            point_x = m_LineChart->mapToValue(event->localPos()).x();
            point_y = m_LineChart->mapToValue(event->localPos()).y();
            crossx_Series->append(-1,point_y);
            crossx_Series->append(1,point_y);

            crossy_Series->append(point_x,-2);
            crossy_Series->append(point_x,2);}


            m_chartvalue_X->setText(QString(mouse_move_X).arg(m_LineChart->mapToValue(event->localPos()).x()));
            m_chartvalue_Y->setText(QString(mouse_move_Y).arg(m_LineChart->mapToValue(event->localPos()).y()));


            if(tooltip_trigger == 1){
                tip->showText(event->globalPos(),QString("X: %1 Y: %2").arg(m_LineChart->mapToValue(event->localPos()).x()).arg(m_LineChart->mapToValue(event->localPos()).y()),this,this->rect(),36000);
            }
            else{tip->hideText();}


        }else{
            m_chartvalue_X->setText(QString(mouse_X));
            m_chartvalue_Y->setText(QString(mouse_Y));
        }
    }else
    {
        m_chartvalue_X->setText(QString(mouse_X));
        m_chartvalue_Y->setText(QString(mouse_Y));
    }


    if((event->x() - m_LineChart1->plotArea().left() +1 >=0) && (m_LineChart1->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart1->plotArea().bottom() -0.0001 <=0) && (m_LineChart1->plotArea().top() - event->y() -0.0001 <=0))
        {

            if(cross_trigger == 1 && current_chart == 1){
            crossx__Series->clear();
            crossy__Series->clear();
            point_x = m_LineChart1->mapToValue(event->localPos()).x();
            point_y = m_LineChart1->mapToValue(event->localPos()).y();
            crossx__Series->append(-1,point_y);
            crossx__Series->append(1,point_y);

            crossy__Series->append(point_x,-2);
            crossy__Series->append(point_x,2);}

            m_chartvalue_X1->setText(QString(mouse_move_X).arg(m_LineChart1->mapToValue(event->localPos()).x()));
            m_chartvalue_Y1->setText(QString(mouse_move_Y).arg(m_LineChart1->mapToValue(event->localPos()).y()));

        }else{
            m_chartvalue_X1->setText(QString(mouse_X));
            m_chartvalue_Y1->setText(QString(mouse_Y));
        }
    }else
    {
        m_chartvalue_X1->setText(QString(mouse_X));
        m_chartvalue_Y1->setText(QString(mouse_Y));
    }



}
void chartview::mouseReleaseEvent(QMouseEvent *event)
{

    rubberBand->hide();

    if(zoom_count == 1 && current_chart == 0){
    if((event->x() - m_LineChart->plotArea().left() +1 >=0) && (m_LineChart->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart->plotArea().bottom() -0.0001 <=0) && (m_LineChart->plotArea().top() - event->y() -0.0001 <=0))
        {

                zoom_point2_x = m_LineChart->mapToValue(event->localPos()).x();
                zoom_point2_y = m_LineChart->mapToValue(event->localPos()).y();

                if(zoom_point1_x < zoom_point2_x){
                    m_AxisX->setRange(zoom_point1_x,zoom_point2_x);
                }else{m_AxisX->setRange(zoom_point2_x,zoom_point1_x);}

                if(zoom_point1_y < zoom_point2_y){
                    m_AxisY->setRange(zoom_point1_y,zoom_point2_y);
                }else{m_AxisY->setRange(zoom_point2_y,zoom_point1_y);}



        }
    }}
    if(zoom_count == 1 && current_chart == 1){
    if((event->x() - m_LineChart1->plotArea().left() +1 >=0) && (m_LineChart1->plotArea().right() - event->x() +1 >=0))
    {
        if((event->y() - m_LineChart1->plotArea().bottom() -0.0001 <=0) && (m_LineChart1->plotArea().top() - event->y() -0.0001 <=0))
        {

                zoom_point2_x = m_LineChart1->mapToValue(event->localPos()).x();
                zoom_point2_y = m_LineChart1->mapToValue(event->localPos()).y();

                if(zoom_point1_x < zoom_point2_x){
                    m_AxisX1->setRange(zoom_point1_x,zoom_point2_x);
                }else{m_AxisX1->setRange(zoom_point2_x,zoom_point1_x);}

                if(zoom_point1_y < zoom_point2_y){
                    m_AxisY1->setRange(zoom_point1_y,zoom_point2_y);
                }else{m_AxisY1->setRange(zoom_point2_y,zoom_point1_y);}

        }
    }}
}
void chartview::tooltip(QPointF point, bool state)
{

    qDebug()<<"receive";
    if (state)
    {
       tooltip_trigger = 1;
       int i = point.x();
       i += 1;

    } else {
       tooltip_trigger = 0;
    }

}
void chartview::attach_Axis()
{
    fitting_Series3->attachAxis(m_AxisX);
    fitting_Series3->attachAxis(m_AxisY);

    m_Series0->attachAxis(m_AxisX);
    m_Series0->attachAxis(m_AxisY);

    m_Series1->attachAxis(m_AxisX);
    m_Series1->attachAxis(m_AxisY);

    m_Series2->attachAxis(m_AxisX);
    m_Series2->attachAxis(m_AxisY);

    m_Series3->attachAxis(m_AxisX);
    m_Series3->attachAxis(m_AxisY);

    m_Series4->attachAxis(m_AxisX);
    m_Series4->attachAxis(m_AxisY);

    m_Series5->attachAxis(m_AxisX);
    m_Series5->attachAxis(m_AxisY);


    input_Series0->attachAxis(m_AxisX1);
    input_Series0->attachAxis(m_AxisY1);

    input_Series1->attachAxis(m_AxisX1);
    input_Series1->attachAxis(m_AxisY1);

    input_Series2->attachAxis(m_AxisX1);
    input_Series2->attachAxis(m_AxisY1);

    input_Series3->attachAxis(m_AxisX1);
    input_Series3->attachAxis(m_AxisY1);

    combine_Series0->attachAxis(m_AxisX1);
    combine_Series0->attachAxis(m_AxisY1);

    combine_Series1->attachAxis(m_AxisX1);
    combine_Series1->attachAxis(m_AxisY1);

    combine_Series2->attachAxis(m_AxisX1);
    combine_Series2->attachAxis(m_AxisY1);


    mark_Series1->attachAxis(m_AxisX);
    mark_Series1->attachAxis(m_AxisY);

    mark_Series2->attachAxis(m_AxisX);
    mark_Series2->attachAxis(m_AxisY);

    mark_Series3->attachAxis(m_AxisX);
    mark_Series3->attachAxis(m_AxisY);

    mark_Series4->attachAxis(m_AxisX);
    mark_Series4->attachAxis(m_AxisY);

    mark_Series5->attachAxis(m_AxisX);
    mark_Series5->attachAxis(m_AxisY);

    mark_Series6->attachAxis(m_AxisX);
    mark_Series6->attachAxis(m_AxisY);


    mark_Series1_->attachAxis(m_AxisX1);
    mark_Series1_->attachAxis(m_AxisY1);

    mark_Series2_->attachAxis(m_AxisX1);
    mark_Series2_->attachAxis(m_AxisY1);

    mark_Series3_->attachAxis(m_AxisX1);
    mark_Series3_->attachAxis(m_AxisY1);

    mark_Series4_->attachAxis(m_AxisX1);
    mark_Series4_->attachAxis(m_AxisY1);

    mark_Series5_->attachAxis(m_AxisX1);
    mark_Series5_->attachAxis(m_AxisY1);

    mark_Series6_->attachAxis(m_AxisX1);
    mark_Series6_->attachAxis(m_AxisY1);


    crossx_Series->attachAxis(m_AxisX);
    crossx_Series->attachAxis(m_AxisY);

    crossy_Series->attachAxis(m_AxisX);
    crossy_Series->attachAxis(m_AxisY);

    crossx__Series->attachAxis(m_AxisX1);
    crossx__Series->attachAxis(m_AxisY1);

    crossy__Series->attachAxis(m_AxisX1);
    crossy__Series->attachAxis(m_AxisY1);


}
void chartview::attach_log_Axis()
{

    fitting_Series3->detachAxis(m_AxisX);
    fitting_Series3->detachAxis(m_AxisY);

    m_Series0->detachAxis(m_AxisX);
    m_Series0->detachAxis(m_AxisY);

    m_Series1->detachAxis(m_AxisX);
    m_Series1->detachAxis(m_AxisY);

    m_Series2->detachAxis(m_AxisX);
    m_Series2->detachAxis(m_AxisY);

    m_Series3->detachAxis(m_AxisX);
    m_Series3->detachAxis(m_AxisY);

    m_Series4->detachAxis(m_AxisX);
    m_Series4->detachAxis(m_AxisY);

    m_Series5->detachAxis(m_AxisX);
    m_Series5->detachAxis(m_AxisY);


    input_Series0->detachAxis(m_AxisX1);
    input_Series0->detachAxis(m_AxisY1);

    input_Series1->detachAxis(m_AxisX1);
    input_Series1->detachAxis(m_AxisY1);

    input_Series2->detachAxis(m_AxisX1);
    input_Series2->detachAxis(m_AxisY1);

    input_Series3->detachAxis(m_AxisX1);
    input_Series3->detachAxis(m_AxisY1);

    combine_Series0->detachAxis(m_AxisX1);
    combine_Series0->detachAxis(m_AxisY1);

    combine_Series1->detachAxis(m_AxisX1);
    combine_Series1->detachAxis(m_AxisY1);

    combine_Series2->detachAxis(m_AxisX1);
    combine_Series2->detachAxis(m_AxisY1);


    mark_Series1->detachAxis(m_AxisX);
    mark_Series1->detachAxis(m_AxisY);

    mark_Series2->detachAxis(m_AxisX);
    mark_Series2->detachAxis(m_AxisY);

    mark_Series3->detachAxis(m_AxisX);
    mark_Series3->detachAxis(m_AxisY);

    mark_Series4->detachAxis(m_AxisX);
    mark_Series4->detachAxis(m_AxisY);

    mark_Series5->detachAxis(m_AxisX);
    mark_Series5->detachAxis(m_AxisY);

    mark_Series6->detachAxis(m_AxisX);
    mark_Series6->detachAxis(m_AxisY);

    mark_Series1_->detachAxis(m_AxisX1);
    mark_Series1_->detachAxis(m_AxisY1);

    mark_Series2_->detachAxis(m_AxisX1);
    mark_Series2_->detachAxis(m_AxisY1);

    mark_Series3_->detachAxis(m_AxisX1);
    mark_Series3_->detachAxis(m_AxisY1);

    mark_Series4_->detachAxis(m_AxisX1);
    mark_Series4_->detachAxis(m_AxisY1);

    mark_Series5_->detachAxis(m_AxisX1);
    mark_Series5_->detachAxis(m_AxisY1);

    mark_Series6_->detachAxis(m_AxisX1);
    mark_Series6_->detachAxis(m_AxisY1);


    crossx_Series->detachAxis(m_AxisX);
    crossx_Series->detachAxis(m_AxisY);

    crossy_Series->detachAxis(m_AxisX);
    crossy_Series->detachAxis(m_AxisY);

    crossx__Series->detachAxis(m_AxisX1);
    crossx__Series->detachAxis(m_AxisY1);

    crossy__Series->detachAxis(m_AxisX1);
    crossy__Series->detachAxis(m_AxisY1);

}
