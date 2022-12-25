#include "theapp.h"
#include "ui_theapp.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QPushButton>
#include<QFont>
#include<QDebug>
#include<QDialog>
#include<QFile>
#include<QFileDialog>
#include<QtMath>

theapp::theapp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::theapp)
{
    ui->setupUi(this);

    setFixedSize(1200,900);
    QFont titlefont("Times New Roman");
    setWindowTitle("ALHPA MODEL");  //A Multitask Visualized Software for Correlation Analysis and Models Prediction of Permeability of Hydrate Sediment
    setFont(titlefont);


    this->calwidget = new Calculate;
    m_LineChartview->setGeometry(190,50,1000,820);
    m_LineChartview->setMouseTracking(true);

    QMenuBar *bar = menuBar();
    bar->setStyleSheet(barstyle);

    setMenuBar(bar);
    QMenu *filemenu = bar->addMenu("File");
    QMenu *workmenu = bar->addMenu("Display");
    QMenu *toolmenu = bar->addMenu("Tools");
    QMenu *setmenu = bar->addMenu("Settings");
    QMenu *analysemenu = bar->addMenu("Analyze");
    QMenu *helpmenu = bar->addMenu("Help");

    QMenu *filemenu_output_child = new QMenu();
    QMenu *filemenu_input_child = new QMenu();
    QMenu *toolmenu_clear_child = new QMenu();

    QAction * input = filemenu->addAction("Import file");
    filemenu->addSeparator();
    QAction * output = filemenu->addAction("Export file");

    input->setMenu(filemenu_input_child);
    output->setMenu(filemenu_output_child);

    QAction * output_page = filemenu_output_child->addAction("Export Image");
    filemenu_output_child->addSeparator();
    QAction * output_static_data = filemenu_output_child->addAction("Export Excel File");


    QAction * inputdata = filemenu_input_child->addAction("For Model Comparison");
    filemenu_input_child->addSeparator();
    QAction * inputdata_self = filemenu_input_child->addAction("For Data Comparison");

    QAction * calbtn =workmenu->addAction("Calculator");
    workmenu->addSeparator();
    QAction * data_model = workmenu->addAction("Model Comparison");
    workmenu->addSeparator();
    QAction * data_compare = workmenu->addAction("Data Comparison");

    QAction *clear_action =toolmenu->addAction("Clear");
    toolmenu->addSeparator();
    QAction * cross_cursor_btn =toolmenu->addAction("Cross Cursor");
    toolmenu->addSeparator();
    QAction * mark_y_btn =toolmenu->addAction("Markline");
    toolmenu->addSeparator();
    QAction * zoom_btn =toolmenu->addAction("Zoom");

    clear_action->setMenu(toolmenu_clear_child);
    QAction * chartclear0 = toolmenu_clear_child->addAction("Clear Data in Model CSYS");
    toolmenu_clear_child->addSeparator();
    QAction * chartclear1 = toolmenu_clear_child->addAction("Clear Data in Data CSYS");
    toolmenu_clear_child->addSeparator();
    QAction * status_text_clear = toolmenu_clear_child->addAction("Clear Records");
    toolmenu_clear_child->addSeparator();
    QAction * mark0_clear = toolmenu_clear_child->addAction("Clear MarkLines in Model CSYS");
    toolmenu_clear_child->addSeparator();
    QAction * mark1_clear = toolmenu_clear_child->addAction("Clear MarkLines in Data CSYS");


    QAction * set_chart =setmenu->addAction("Coordinate system");


    QAction * tablewidget1_btn =analysemenu->addAction("Statistical Table(Model)");
    analysemenu->addSeparator();
    QAction * tablewidget2_btn =analysemenu->addAction("Statistical Table(Data)");
    analysemenu->addSeparator();
    QAction * analyse_model =analysemenu->addAction("Fitting Analysis");


    QAction * helpfile =helpmenu->addAction("Documents");
    helpmenu->addSeparator();
    QAction * excel_example =helpmenu->addAction("Excel Example");


        for(int i=0;i<60;i++)
        {
            input_SH[i] = 0;
            input_kn[i] = 0;
        }


    status_textedit = new QTextEdit(this);
    status_textedit->setReadOnly(true);
    status_textedit->setGeometry(5,50,180,820);
    status_textedit->setLineWrapMode(QTextEdit::WidgetWidth);
    status_textedit->setWordWrapMode(QTextOption::WordWrap);
    status_textedit->setAlignment(Qt::AlignLeft);
    status_textedit->setOverwriteMode(false);
    QFont status_font("Times New Roman");
    status_textedit->setFont(status_font);


    tablewidget1->setWindowTitle("Statistical Table(Model)");
    tablewidget1->setGeometry(200,200,700,800);
    tablewidget1->setRowCount(122);
    tablewidget1->setColumnCount(13);
    tablewidget1->setFrameShape(QFrame::NoFrame);
    tablewidget1->verticalHeader()->setVisible(false);
    tablewidget1->horizontalHeader()->setVisible(false);
    tablewidget1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tablewidget1->setSelectionMode(QAbstractItemView::ExtendedSelection);
    tablewidget1->setFont(status_font);


    for(int i=0;i<6;i++)
    {
     tablewidget1->setSpan(0,2*i+1,1,2);
    }
    QStringList string_list;
    string_list<<"Original Data"<<"Tokyo model"<<"Patchy model"<<"G-C model"<<"P-F model"<<"Hybrid model";
    for(int i=0;i<6;i++)
    {
     tablewidget1->setItem(0,2*i+1, new QTableWidgetItem(string_list[i]));
     tablewidget1->setItem(1,2*i+1, new QTableWidgetItem("Saturation"));
     tablewidget1->setItem(1,2*i+2, new QTableWidgetItem("Permeability"));
    }
    for(int i=2;i<122;i++)
    {
     tablewidget1->setItem(i,0, new QTableWidgetItem(QString::number(i-1)));
    }
    for(int i=2;i<122;i++)
    {
        for (int j=1;j<13;j++)
        {
            tablewidget1->setItem(i,j, new QTableWidgetItem);
        }
    }        


        tablewidget2->setWindowTitle("Statistical Table(Data)");
        tablewidget2->setGeometry(200,200,700,800);
        tablewidget2->setRowCount(122);
        tablewidget2->setColumnCount(15);
        tablewidget2->setFrameShape(QFrame::NoFrame);
        tablewidget2->verticalHeader()->setVisible(false);
        tablewidget2->horizontalHeader()->setVisible(false);
        tablewidget2->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tablewidget2->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tablewidget2->setFont(status_font);

        for(int i=0;i<7;i++)
        {
         tablewidget2->setSpan(0,2*i+1,1,2);
        }

        QStringList string_list1;
        string_list1<<"Original Data 1"<<"Original Data 2"<<"Original Data 3"<<"Original Data 4"<<"Combined Data 1"<<"Combined Data 2"<<"Combined Data 3";
        for(int i=0;i<7;i++)
        {
         tablewidget2->setItem(0,2*i+1, new QTableWidgetItem(string_list1[i]));
         tablewidget2->setItem(1,2*i+1, new QTableWidgetItem("Saturation"));
         tablewidget2->setItem(1,2*i+2, new QTableWidgetItem("Permeability"));
        }
        for(int i=2;i<122;i++)
        {
         tablewidget2->setItem(i,0, new QTableWidgetItem(QString::number(i-1)));
        }
        for(int i=2;i<122;i++)
        {
            for (int j=1;j<15;j++)
            {
                tablewidget2->setItem(i,j, new QTableWidgetItem);
            }
        }



    connect(calbtn,&QAction::triggered,[=](){
        calwidget->show();
        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Calculator works.");
    });

    connect(tablewidget1_btn,&QAction::triggered,[=](){

        int i = 2;
        int j = 1;
        for(;i<122;i++)
        {
            if(m_LineChartview->input_SH[i-2] == 0 && m_LineChartview->input_kn[i-2] == 0){break;}
            j = 1;
            for (;j<13;j++)
            {                
                if(j == 1){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 2){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_kn[i-2]));}
                if(j == 3){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 4){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->Masuda_kn_group[i-2]));}
                if(j == 5){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 6){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->Patchy_kr_group[i-2]));}
                if(j == 7){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 8){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->GC_kn_group[i-2]));}
                if(j == 9){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 10){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->PF_kn_group[i-2]));}
                if(j == 11){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->input_SH[i-2]));}
                if(j == 12){tablewidget1->item(i,j)->setText(QString::number(m_LineChartview->Hybrid_kn_group[i-2]));}

            }
        }

        tablewidget1->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Statistical Table(Model) works. Check import data and model data.");

    });


    connect(tablewidget2_btn,&QAction::triggered,[=](){

        int i = 2;
        int j = 1;
        for(;i<122;i++)
        {
            if(m_LineChartview->input_kn0[i-2] == 0 && m_LineChartview->input_SH0[i-2] == 0){break;}
            j = 1;
            for (;j<3;j++)
            {
                if(j == 1){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_SH0[i-2]));}
                if(j == 2){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_kn0[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->input_kn1[i-2] == 0 && m_LineChartview->input_SH1[i-2] == 0){break;}
            j = 3;
            for (;j<5;j++)
            {
                if(j == 3){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_SH1[i-2]));}
                if(j == 4){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_kn1[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->input_kn2[i-2] == 0 && m_LineChartview->input_SH2[i-2] == 0){break;}
            j = 5;
            for (;j<7;j++)
            {
                if(j == 5){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_SH2[i-2]));}
                if(j == 6){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_kn2[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->input_kn3[i-2] == 0 && m_LineChartview->input_SH3[i-2] == 0){break;}
            j = 7;
            for (;j<9;j++)
            {
                if(j == 7){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_SH3[i-2]));}
                if(j == 8){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->input_kn3[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->combine_kn0[i-2] == 0 && m_LineChartview->combine_SH0[i-2] == 0){break;}
            j = 9;
            for (;j<11;j++)
            {
                if(j == 9){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_SH0[i-2]));}
                if(j == 10){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_kn0[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->combine_kn1[i-2] == 0 && m_LineChartview->combine_SH1[i-2] == 0){break;}
            j = 11;
            for (;j<13;j++)
            {
                if(j == 11){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_SH1[i-2]));}
                if(j == 12){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_kn1[i-2]));}
            }
        }
        i = 2;

        for(;i<122;i++)
        {
            if(m_LineChartview->combine_kn2[i-2] == 0 && m_LineChartview->combine_SH2[i-2] == 0){break;}
            j = 13;
            for (;j<15;j++)
            {
                if(j == 13){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_SH2[i-2]));}
                if(j == 14){tablewidget2->item(i,j)->setText(QString::number(m_LineChartview->combine_kn2[i-2]));}
            }
        }
        i = 2;


        tablewidget2->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Statistical Table(Data) works. Check import data and Combined data.");

    });



    connect(zoom_btn,&QAction::triggered,[=](){
        if(m_LineChartview->zoom_count == 0){

            m_LineChartview->zoom_count = 1;

            m_LineChartview->setRubberBand(QChartView::RectangleRubberBand);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Zoom function works. Clicking this button again will stop zoom function.");

        }else{
        if(m_LineChartview->zoom_count == 1){

            m_LineChartview->zoom_count = 0;

            m_LineChartview->setRubberBand(QChartView::NoRubberBand);

            if(m_LineChartview->current_chart == 0){

                m_LineChartview->m_AxisX->setRange(x_range1_text.toDouble(),x_range2_text.toDouble());
                m_LineChartview->m_AxisY->setRange(y_range1_text.toDouble(),y_range2_text.toDouble());

            }
            if(m_LineChartview->current_chart == 1){

                m_LineChartview->m_AxisX1->setRange(x_range1_text_.toDouble(),x_range2_text_.toDouble());
                m_LineChartview->m_AxisY1->setRange(y_range1_text_.toDouble(),y_range2_text_.toDouble());

            }
            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Zoom function ends. Axis initializes.");
        }}

    });


    connect(cross_cursor_btn,&QAction::triggered,[=](){

        if(cross_count == 0)
        {

            cross_count = 1;
            m_LineChartview->cross_trigger = 1;

            this->setCursor(Qt::CrossCursor);
            m_LineChartview->m_LineChart->setAnimationOptions(QChart::NoAnimation);
            m_LineChartview->m_LineChart1->setAnimationOptions(QChart::NoAnimation);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Cross Cursor works. Clicking this button again will stop this function.");
        }else{

        if(cross_count == 1)
        {

            cross_count = 0;
            m_LineChartview->cross_trigger = 0;

            m_LineChartview->crossx_Series->clear();
            m_LineChartview->crossy_Series->clear();

            m_LineChartview->crossx__Series->clear();
            m_LineChartview->crossy__Series->clear();

            this->setCursor(Qt::ArrowCursor);
            m_LineChartview->m_LineChart->setAnimationOptions(QChart::AllAnimations);
            m_LineChartview->m_LineChart1->setAnimationOptions(QChart::AllAnimations);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Cross Cursor ends.");

        }}
    });


    connect(mark_y_btn,&QAction::triggered,[=](){

        if(mark_y_count == 0)
        {

            mark_y_count = 1;
            m_LineChartview->click_trigger = 1;

            this->setCursor(Qt::CrossCursor);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("MarkLines work. Upper limited number of MarkLines is 6. Clicking this button again will stop to mark.");
        }else{
        if(mark_y_count == 1)
        {

            mark_y_count = 0;
            m_LineChartview->click_trigger = 0;

            this->setCursor(Qt::ArrowCursor);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Stop to mark.");

        }}
    });



    connect(inputdata,&QAction::triggered,[=](){


        QMessageBox::information(this,"Import Tips","The format of file needs to reach the following requirments.\n"
                                                "1. Microsoft Excel.\n"
                                                "2. Data array in order of column. The group has two columns: Saturation data and Permeability data. "
                                                "Model Compare function can only import single file in one time.\n"
                                                "3. Data will be read from the third row of the file.\n"
                                                "More questions can be answered in Help function.");



        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Import original data");

        for(int i=0;i<60;i++)
        {

            m_LineChartview->fitting3_SH[i] = 0;
            m_LineChartview->fitting3_kn[i] = 0;

            m_LineChartview->input_SH[i] = 0;
            m_LineChartview->input_kn[i] = 0;

            m_LineChartview->Masuda_SH_group[i]=0;
            m_LineChartview->Masuda_kn_group[i]=0;

            m_LineChartview->Patchy_SH_group[i]=0;
            m_LineChartview->Patchy_kr_group[i]=0;

            m_LineChartview->Hybrid_SH_group[i]=0;
            m_LineChartview->Hybrid_kn_group[i]=0;

            m_LineChartview->GC_SH_group[i]=0;
            m_LineChartview->GC_kn_group[i]=0;

            m_LineChartview->PF_SH_group[i]=0;
            m_LineChartview->PF_kn_group[i]=0;
        }


        y_ave = 0;
        RMSE_Masuda = 0;
        RMSE_Patchy = 0;
        RMSE_GC = 0;
        RMSE_PF = 0;
        RMSE_Hybrid = 0;

        QAxObject excel("Excel.Application");
        excel.setProperty("Visible", false);
        excel.setProperty("DisplayAlerts", false);
        QAxObject *work_books = excel.querySubObject("WorkBooks");
        QString filePath=QFileDialog::getOpenFileName(this,tr("Select file"),".",tr(" (*.xlsx)"));
        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("The address of import file is: ");
        status_textedit->append(filePath);

        if(!filePath.isEmpty())
        {

         work_books->dynamicCall("Open (const QString&)", filePath);
         QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
         QAxObject *work_sheets = work_book->querySubObject("Sheets");
         int sheet_count = work_sheets->property("Count").toInt();
         qDebug() <<"the number of sheets:"<<sheet_count;
         if(sheet_count > 0)
         {
            QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
            QAxObject *used_range = work_sheet->querySubObject("UsedRange");
            QAxObject *rows = used_range->querySubObject("Rows");
            int row_count = rows->property("Count").toInt();
            qDebug() <<"the number of used rows:"<<row_count;

            QString txt;
            QString txt1;
            QString txt2;
            N = 0;
            for(int i=3;i <= 62;i++)
            {
                txt = work_sheet->querySubObject("Cells(int,int)", i, 1)->property("Value").toString();
                if(txt == ""){break;}
                m_LineChartview->fitting3_SH[i-3] = txt.toDouble();
                m_LineChartview->input_SH[i-3] = txt.toDouble();
                m_LineChartview->Masuda_SH_group[i-3] = txt.toDouble();
                m_LineChartview->Patchy_SH_group[i-3] = txt.toDouble();
                m_LineChartview->GC_SH_group[i-3] = txt.toDouble();
                m_LineChartview->PF_SH_group[i-3] = txt.toDouble();
                m_LineChartview->Hybrid_SH_group[i-3] = txt.toDouble();

                x_sum += txt.toDouble();
                x2_sum += (txt.toDouble()) * (txt.toDouble());
                x3_sum += (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble());
                x4_sum += (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble());
                x5_sum += (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble());
                x6_sum += (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble());

                txt1 = work_sheet->querySubObject("Cells(int,int)", i, 2)->property("Value").toString();
                if(txt1 == ""){break;}
                m_LineChartview->input_kn[i-3] = txt1.toDouble();

                y_sum += txt1.toDouble();
                xy_sum += (txt.toDouble()) * (txt1.toDouble());
                x2y_sum += (txt.toDouble()) * (txt.toDouble()) * (txt1.toDouble());
                x3y_sum += (txt.toDouble()) * (txt.toDouble()) * (txt.toDouble()) * (txt1.toDouble());

                N += 1;

            }


            work_book->dynamicCall("Close(Boolean)", false);
            excel.dynamicCall("Quit(void)");
            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Original Data have been imported for Model Compare function.");
            status_textedit->append("SH  kn");
            for(int i=0;i < 60;i++)
            {
                if(m_LineChartview->input_SH[i] == 0 && m_LineChartview->input_kn[i] == 0){break;}

                txt = QString("%1").arg(m_LineChartview->input_SH[i], 0, 'f', 5);
                txt1 = QString("%1").arg(m_LineChartview->input_kn[i], 0, 'f', 5);
                txt2 = txt + "  " + txt1;
                status_textedit->append(txt2);

            }

         }
        }

        double temp1 = 0;
        double k = 0;
        int i1 = 0;
        int small_count1 = 0;
        int small_count2 = 0;


        for(int i=0;i<60;i++)
        {
            if(m_LineChartview->Masuda_SH_group[i] == 0 && m_LineChartview->Masuda_SH_group[i+1] == 0 && m_LineChartview->Masuda_SH_group[i+2] == 0)
            {break;}

            for (i1 = i + 1; i1 < 60; i1++)
            {
                if(m_LineChartview->Masuda_SH_group[i1] ==0)
                {continue;}

                if (m_LineChartview->Masuda_SH_group[i] > m_LineChartview->Masuda_SH_group[i1])
                {
                    temp1 = m_LineChartview->Masuda_SH_group[i1];
                    m_LineChartview->Masuda_SH_group[i1] = m_LineChartview->Masuda_SH_group[i];
                    m_LineChartview->Masuda_SH_group[i] = temp1;

                }
                if (m_LineChartview->Masuda_SH_group[i] == m_LineChartview->Masuda_SH_group[i1])
                {
                    small_count1 = i;
                    small_count2 = i1;
                    k = m_LineChartview->Masuda_SH_group[i1];
                }
            }
            if(small_count1 != 0 && k == m_LineChartview->Masuda_SH_group[i])
            {
                if (m_LineChartview->Masuda_SH_group[small_count1] <= m_LineChartview->Masuda_SH_group[small_count2])
                {
                    temp1 = m_LineChartview->Masuda_SH_group[small_count1 + 1];
                    m_LineChartview->Masuda_SH_group[small_count1 + 1] = m_LineChartview->Masuda_SH_group[small_count2];
                    m_LineChartview->Masuda_SH_group[small_count2] = temp1;

                }else{

                    temp1 = m_LineChartview->Masuda_SH_group[small_count1];
                    m_LineChartview->Masuda_SH_group[small_count1] = m_LineChartview->Masuda_SH_group[small_count2];
                    m_LineChartview->Masuda_SH_group[small_count2] = temp1;

                    temp1 = m_LineChartview->Masuda_SH_group[small_count1 + 1];
                    m_LineChartview->Masuda_SH_group[small_count1 + 1] = m_LineChartview->Masuda_SH_group[small_count2];
                    m_LineChartview->Masuda_SH_group[small_count2] = temp1;

                }
                small_count1 = 0;
                small_count2 = 0;
            }
            small_count1 = 0;
            small_count2 = 0;
        }

        for (int i = 0;i<60;i++) {

            m_LineChartview->input_SH[i] = m_LineChartview->Masuda_SH_group[i];
            m_LineChartview->fitting3_SH[i] = m_LineChartview->Masuda_SH_group[i];
            m_LineChartview->Patchy_SH_group[i] = m_LineChartview->Masuda_SH_group[i];
            m_LineChartview->GC_SH_group[i] = m_LineChartview->Masuda_SH_group[i];
            m_LineChartview->PF_SH_group[i] = m_LineChartview->Masuda_SH_group[i];
            m_LineChartview->Hybrid_SH_group[i] = m_LineChartview->Masuda_SH_group[i];

        }
    });



    connect(inputdata_self,&QAction::triggered,[=](){

        QMessageBox::information(this,"Export Tips","The format of file needs to reach the following requirments:\n"
                                                "1. Microsoft Excel.\n"
                                                "2. Data array in order of column. Every group has three columns: Saturation data, Permeability data and empty column.\n"
                                                "3. Data will be read from the third row of the file.\n"
                                                "More questions can be answered in Help function.");

        if(input_file_num >= 4){

            QMessageBox::information(this,"Warning","The number of import data groups can not be more than 4.");
            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("The number of import data groups has reached the upper limit.");
        }else{

        QAxObject excel1("Excel.Application");
        excel1.setProperty("Visible", false);
        excel1.setProperty("DisplayAlerts", false);
        QAxObject *work_books = excel1.querySubObject("WorkBooks");
        QString filePath=QFileDialog::getOpenFileName(this,tr("Select File"),".",tr(" (*.xlsx)"));
        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("The address of import file is:");
        status_textedit->append(filePath);

        if(!filePath.isEmpty())
        {

         work_books->dynamicCall("Open (const QString&)", filePath);
         QAxObject *work_book = excel1.querySubObject("ActiveWorkBook");
         QAxObject *work_sheets = work_book->querySubObject("Sheets");
         int sheet_count = work_sheets->property("Count").toInt();
         qDebug() <<"the number of sheets:"<<sheet_count;
         if(sheet_count > 0)
         {
            QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", 1);
            QAxObject *used_range = work_sheet->querySubObject("UsedRange");
            QAxObject *rows = used_range->querySubObject("Rows");
            int row_count = rows->property("Count").toInt();
            qDebug() <<"the number of used rows:"<<row_count;

            QString txt;
            if(input_file_num == 0){
                input_box0_name = work_sheet->querySubObject("Cells(int,int)", 1, 1)->property("Value").toString();
                m_LineChartview->input_Series0->setName(input_box0_name);
                currentTime = QTime::currentTime();
                currentTime_text = currentTime.toString("hh:mm:ss");
                status_textedit->append(currentTime_text);
                status_textedit->append("The following data will be showed in limited decimal places\n\nFirst Group:");
                status_textedit->append("SH  kn");

            for(int i=3;i <= 62;i++)
            {
                if(work_sheet->querySubObject("Cells(int,int)", i, 1)->property("Value").toString() == ""
                        && work_sheet->querySubObject("Cells(int,int)", i, 2)->property("Value").toString() == ""){break;}
                txt = work_sheet->querySubObject("Cells(int,int)", i, 1)->property("Value").toString();
                m_LineChartview->input_SH0[i-3] = txt.toDouble();

                temp_text = QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                temp_text += "  ";

                txt = work_sheet->querySubObject("Cells(int,int)", i, 2)->property("Value").toString();
                m_LineChartview->input_kn0[i-3] = txt.toDouble();

                temp_text += QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                status_textedit->append(temp_text);

            }
                if(work_sheet->querySubObject("Cells(int,int)", 3, 4)->property("Value").toString() != "")
                {input_file_num++;}
            }



            if(input_file_num == 1){
                input_box1_name = work_sheet->querySubObject("Cells(int,int)", 1, 4)->property("Value").toString();
                m_LineChartview->input_Series1->setName(input_box1_name);

                status_textedit->append("\nSecond Group:");
                status_textedit->append("SH  kn");
            for(int i=3;i <= 62;i++)
            {
                if(work_sheet->querySubObject("Cells(int,int)", i, 4)->property("Value").toString() == ""
                        && work_sheet->querySubObject("Cells(int,int)", i, 5)->property("Value").toString() == ""){break;}
                txt = work_sheet->querySubObject("Cells(int,int)", i, 4)->property("Value").toString();
                m_LineChartview->input_SH1[i-3] = txt.toDouble();

                temp_text = QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                temp_text += "  ";

                txt = work_sheet->querySubObject("Cells(int,int)", i, 5)->property("Value").toString();
                m_LineChartview->input_kn1[i-3] = txt.toDouble();

                temp_text += QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                status_textedit->append(temp_text);

            }
            if(work_sheet->querySubObject("Cells(int,int)", 3, 7)->property("Value").toString() != "")
            {input_file_num++;}
            }


            if(input_file_num == 2){
                input_box2_name = work_sheet->querySubObject("Cells(int,int)", 1, 7)->property("Value").toString();
                m_LineChartview->input_Series2->setName(input_box2_name);

                status_textedit->append("\nThird Group:");
                status_textedit->append("SH  kn");
            for(int i=3;i <= 62;i++)
            {
                if(work_sheet->querySubObject("Cells(int,int)", i, 7)->property("Value").toString() == ""
                        && work_sheet->querySubObject("Cells(int,int)", i, 8)->property("Value").toString() == ""){break;}
                txt = work_sheet->querySubObject("Cells(int,int)", i, 7)->property("Value").toString();
                m_LineChartview->input_SH2[i-3] = txt.toDouble();

                temp_text = QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                temp_text += "  ";

                txt = work_sheet->querySubObject("Cells(int,int)", i, 8)->property("Value").toString();
                m_LineChartview->input_kn2[i-3] = txt.toDouble();

                temp_text += QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                status_textedit->append(temp_text);

            }

            if(work_sheet->querySubObject("Cells(int,int)", 3, 10)->property("Value").toString() != "")
            {input_file_num++;}
            }


            if(input_file_num == 3){
                input_box3_name = work_sheet->querySubObject("Cells(int,int)", 1, 10)->property("Value").toString();
                m_LineChartview->input_Series3->setName(input_box3_name);

                status_textedit->append("\nFourth Group:");
                status_textedit->append("SH  kn");
            for(int i=3;i <= 62;i++)
            {
                if(work_sheet->querySubObject("Cells(int,int)", i, 10)->property("Value").toString() == ""
                        && work_sheet->querySubObject("Cells(int,int)", i, 11)->property("Value").toString() == ""){break;}
                txt = work_sheet->querySubObject("Cells(int,int)", i, 10)->property("Value").toString();
                m_LineChartview->input_SH3[i-3] = txt.toDouble();

                temp_text = QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                temp_text += "  ";

                txt = work_sheet->querySubObject("Cells(int,int)", i, 11)->property("Value").toString();
                m_LineChartview->input_kn3[i-3] = txt.toDouble();

                temp_text += QString("%1").arg(txt.toDouble(), 0, 'f', 5);
                status_textedit->append(temp_text);

            }
            }


            work_book->dynamicCall("Close(Boolean)", false);
            excel1.dynamicCall("Quit(void)");

            status_textedit->append("Original Data have been imported for Model Compare function.");

         }
        }
        }

    });


    connect(output_static_data,&QAction::triggered,[=](){

        QString filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.xlsx)"));
        if(!filepath.isEmpty()){
            QAxObject *excel = new QAxObject(this);
            excel->setControl("Excel.Application");
            excel->dynamicCall("SetVisible (bool Visible)","false");
            excel->setProperty("DisplayAlerts", false);
            QAxObject *workbooks = excel->querySubObject("WorkBooks");
            workbooks->dynamicCall("Add");
            QAxObject *workbook = excel->querySubObject("ActiveWorkBook");
            QAxObject *worksheets = workbook->querySubObject("Sheets");
            QAxObject *worksheet = worksheets->querySubObject("Item(int)",1);
            QAxObject *cellA,*cellB,*cellC,*cellD,*cellE,*cellF,*cellG;
            int cellrow=1;
            QString B="B"+QString::number(cellrow);
            QString C="C"+QString::number(cellrow);
            QString D="D"+QString::number(cellrow);
            QString E="E"+QString::number(cellrow);
            QString F="F"+QString::number(cellrow);
            QString G="G"+QString::number(cellrow);

            cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
            cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
            cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
            cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
            cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
            cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);

            cellB->dynamicCall("SetValue(const QVariant&)",QVariant("Combined Data 1"));
            cellD->dynamicCall("SetValue(const QVariant&)",QVariant("Combined Data 2"));
            cellF->dynamicCall("SetValue(const QVariant&)",QVariant("Combined Data 3"));
            cellrow++;

            for(int i=0;i<120;i++)
            {
                QString A="A"+QString::number(cellrow);
                QString I=QString::number(i+1);
                cellA = worksheet->querySubObject("Range(QVariant, QVariant)",A);
                cellA->dynamicCall("SetValue(const QVariant&)",QVariant(I));

                cellrow++;
            }

            cellrow = 2;

            for(int i=0;cellrow <= 121;cellrow++)
            {
                QString B="B"+QString::number(cellrow);
                QString C="C"+QString::number(cellrow);
                QString D="D"+QString::number(cellrow);
                QString E="E"+QString::number(cellrow);
                QString F="F"+QString::number(cellrow);
                QString G="G"+QString::number(cellrow);

                cellB = worksheet->querySubObject("Range(QVariant, QVariant)",B);
                cellC = worksheet->querySubObject("Range(QVariant, QVariant)",C);
                cellD = worksheet->querySubObject("Range(QVariant, QVariant)",D);
                cellE = worksheet->querySubObject("Range(QVariant, QVariant)",E);
                cellF = worksheet->querySubObject("Range(QVariant, QVariant)",F);
                cellG = worksheet->querySubObject("Range(QVariant, QVariant)",G);

                if(m_LineChartview->combine_SH0[i] != 0 || m_LineChartview->combine_kn0[i] != 0){
                cellB->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_SH0[i])));
                cellC->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_kn0[i])));}

                if(m_LineChartview->combine_SH1[i] != 0 || m_LineChartview->combine_kn1[i] != 0){
                cellD->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_SH1[i])));
                cellE->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_kn1[i])));}

                if(m_LineChartview->combine_SH2[i] != 0 || m_LineChartview->combine_kn2[i] != 0){
                cellF->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_SH2[i])));
                cellG->dynamicCall("SetValue(const QVariant&)",QVariant(QString::number(m_LineChartview->combine_kn2[i])));}
                i++;
            }
            workbook->dynamicCall("SaveAs(const QString&)",QDir::toNativeSeparators(filepath));
            workbook->dynamicCall("Close()");
            excel->dynamicCall("Quit()");
            delete excel;
            excel=NULL;

        }

    });



    QStringList RMSE_name_list;
    RMSE_name_list<<"Tokyo model"<<"Patchy model"<<"G-C model"<<"P-F model"<<"Hybrid model";
    QDialog *analyse_dialog = new QDialog(this);
    QFont fit_font("Times New Roman");
    analyse_dialog->setGeometry(300,600,300,250);
    analyse_dialog->setFont(fit_font);
    analyse_dialog->setWindowTitle("Analyze Results");

    analyse_result = new QTextEdit(analyse_dialog);
    analyse_result->setReadOnly(true);
    analyse_result->setGeometry(5,5,290,180);
    analyse_result->setLineWrapMode(QTextEdit::WidgetWidth);
    analyse_result->setWordWrapMode(QTextOption::WordWrap);
    analyse_result->setAlignment(Qt::AlignLeft);
    analyse_result->setOverwriteMode(false);
    analyse_result->setFont(fit_font);

    enforce_show = new QCheckBox(analyse_dialog);
    enforce_show->setText("Highlight Best Fitting Model");
    enforce_show->setCheckState(Qt::Unchecked);
    enforce_show->setGeometry(10,190,290,60);
    enforce_show->setFont(fit_font);

    QList<QLineSeries*>series_list;
    series_list.append(m_LineChartview->m_Series1);
    series_list.append(m_LineChartview->m_Series2);
    series_list.append(m_LineChartview->m_Series3);
    series_list.append(m_LineChartview->m_Series4);
    series_list.append(m_LineChartview->m_Series5);

    connect(enforce_show,&QCheckBox::toggled,[=](){
        if(enforce_show->checkState() == Qt::Unchecked)
        {
           m_LineChartview->m_Series1->setVisible(true);
           m_LineChartview->m_Series2->setVisible(true);
           m_LineChartview->m_Series3->setVisible(true);
           m_LineChartview->m_Series4->setVisible(true);
           m_LineChartview->m_Series5->setVisible(true);

           currentTime = QTime::currentTime();
           currentTime_text = currentTime.toString("hh:mm:ss");
           status_textedit->append(currentTime_text);
           status_textedit->append("Highlight function ends. Display all model curves.");
        }
        if(enforce_show->checkState() == Qt::Checked)
        {
            m_LineChartview->m_Series1->setVisible(false);
            m_LineChartview->m_Series2->setVisible(false);
            m_LineChartview->m_Series5->setVisible(false);
            series_list[RMSE_min_count]->setVisible(true);

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Highlight Best Fitting Model. Hide other model curves.");
        }

     });

    connect(analyse_model,&QAction::triggered,[=](){

        RMSE_Masuda = 0;
        RMSE_Patchy = 0;
        RMSE_GC = 0;
        RMSE_PF = 0;
        RMSE_Hybrid = 0;

        if(Masuda_kn_group[0] == 0 || fit_count == 0){
             QMessageBox::information(this,"Warning","Can not find Model Data. Please run Model Compare function first, then run analysis function.");}else{
         y_ave = y_sum / N;
         for (int i=0;i<N;i++)
         {
            RMSE_Masuda += pow((m_LineChartview->Masuda_kn_group[i] - m_LineChartview->input_kn[i]),2);
            RMSE_Patchy += pow((m_LineChartview->Patchy_kr_group[i] - m_LineChartview->input_kn[i]),2);
            RMSE_GC += pow((m_LineChartview->GC_kn_group[i] - m_LineChartview->input_kn[i]),2);
            RMSE_PF += pow((m_LineChartview->PF_kn_group[i] - m_LineChartview->input_kn[i]),2);
            RMSE_Hybrid += pow((m_LineChartview->Hybrid_kn_group[i] - m_LineChartview->input_kn[i]),2);
         }

            RMSE_Masuda = pow((RMSE_Masuda/N),0.5);
            RMSE_Patchy = pow((RMSE_Patchy/N),0.5);
            RMSE_GC = pow((RMSE_GC/N),0.5);
            RMSE_PF = pow((RMSE_PF/N),0.5);
            RMSE_Hybrid = pow((RMSE_Hybrid/N),0.5);

            RMSE_list.clear();
            RMSE_list<<RMSE_Masuda<<RMSE_Patchy<<RMSE_GC<<RMSE_PF<<RMSE_Hybrid;


            int k = 1;
            RMSE_min_count = 0;
            for(;k<5;k++)
            {
               if(RMSE_list[RMSE_min_count] > RMSE_list[k])
               {
                   RMSE_min_count = k;
               }

            }


            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("The Best Fitting Model:");
            status_textedit->append(RMSE_name_list[RMSE_min_count]);
            status_textedit->append("RMSE:");
            status_textedit->append(QString::number(RMSE_list[RMSE_min_count]));
            status_textedit->append("All models' RMSE: ");
            status_textedit->append(RMSE_name_list[0]);
            status_textedit->append(QString::number(RMSE_list[0]));
            status_textedit->append(RMSE_name_list[1]);
            status_textedit->append(QString::number(RMSE_list[1]));
            status_textedit->append(RMSE_name_list[2]);
            status_textedit->append(QString::number(RMSE_list[2]));
            status_textedit->append(RMSE_name_list[3]);
            status_textedit->append(QString::number(RMSE_list[3]));
            status_textedit->append(RMSE_name_list[4]);
            status_textedit->append(QString::number(RMSE_list[4]));

            analyse_dialog->show();
            analyse_result->clear();
            analyse_result->setTextColor(Qt::red);
            analyse_result->append("The Best Fitting Model:  " + RMSE_name_list[RMSE_min_count]);
            analyse_result->append("RMSE:  " + QString::number(RMSE_list[RMSE_min_count]));
            analyse_result->setTextColor(Qt::black);
            analyse_result->append("All models' RMSE:");
            analyse_result->append(RMSE_name_list[0] + ":  " + QString::number(RMSE_list[0]));
            analyse_result->append(RMSE_name_list[1] + ":  " + QString::number(RMSE_list[1]));
            analyse_result->append(RMSE_name_list[2] + ":  " + QString::number(RMSE_list[2]));
            analyse_result->append(RMSE_name_list[3] + ":  " + QString::number(RMSE_list[3]));
            analyse_result->append(RMSE_name_list[4] + ":  " + QString::number(RMSE_list[4]));

         }
    });


    QDialog *data_model_dialog = new QDialog(this);
    QFont set_font("Times New Roman");
    FirstBox_starbtn = new QPushButton(data_model_dialog);
    FirstBox_starbtn->setText("Model Fitting");
    FirstBox_starbtn->setGeometry(10,255,200,40);
    FirstBox_starbtn->setStyleSheet(this->btnstyle);

    FirstBox_fittingbtn = new QPushButton(data_model_dialog);
    FirstBox_fittingbtn->setText("Cubic Polynomial Fitting");
    FirstBox_fittingbtn->setGeometry(10,305,200,40);
    FirstBox_fittingbtn->setStyleSheet(this->btnstyle_small);

    FirstBox_changebtn = new QPushButton(data_model_dialog);
    FirstBox_changebtn->setText("Factor Change");
    FirstBox_changebtn->setGeometry(10,355,200,40);
    FirstBox_changebtn->setStyleSheet(this->btnstyle);

    FirstBox_backbtn = new QPushButton(data_model_dialog);
    FirstBox_backbtn->setText("Factor Initialization");
    FirstBox_backbtn->setGeometry(10,405,200,40);
    FirstBox_backbtn->setStyleSheet(this->btnstyle);

    data_model_dialog->setGeometry(1200,200,600,450);
    data_model_dialog->setFixedSize(600,450);
    data_model_dialog->setWindowTitle("Model Fitting and Comparision");
    data_model_dialog->setFont(set_font);


    connect(data_model,&QAction::triggered,[=](){

        m_LineChartview->showlabel1->show();
        m_LineChartview->showlabel2->show();
        m_LineChartview->showlabel3->show();
        m_LineChartview->showlabel4->show();
        m_LineChartview->showlabel5->show();
        m_LineChartview->showlabel6->show();

        m_LineChartview->colorlabel1->show();
        m_LineChartview->colorlabel2->show();
        m_LineChartview->colorlabel3->show();
        m_LineChartview->colorlabel4->show();
        m_LineChartview->colorlabel5->show();
        m_LineChartview->colorlabel6->show();

        m_LineChartview->showlabel7->hide();
        m_LineChartview->showlabel8->hide();
        m_LineChartview->showlabel9->hide();
        m_LineChartview->showlabel10->hide();
        m_LineChartview->showlabel11->hide();
        m_LineChartview->showlabel12->hide();
        m_LineChartview->showlabel13->hide();

        m_LineChartview->colorlabel7->hide();
        m_LineChartview->colorlabel8->hide();
        m_LineChartview->colorlabel9->hide();
        m_LineChartview->colorlabel10->hide();
        m_LineChartview->colorlabel11->hide();
        m_LineChartview->colorlabel12->hide();
        m_LineChartview->colorlabel13->hide();


        m_LineChartview->setChart(m_LineChartview->m_LineChart);
        m_LineChartview->current_chart = 0;
        createFirstBox()->setParent(data_model_dialog);
        createSixthBox()->setParent(data_model_dialog);
        create7thBox()->setParent(data_model_dialog);
        create8thBox()->setParent(data_model_dialog);
        data_model_dialog->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Shift to Model Fitting and Comparision mode");
        status_textedit->setTextColor(Qt::red);
        status_textedit->append("It takes time to run Model Fitting function. Please wait a few seconds.");
        status_textedit->setTextColor(Qt::black);

    });


    connect(FirstBox_starbtn,&QPushButton::clicked,[=](){

        Masuda_count_N = 0;
        Patchy_count_N = 0;
        Hybrid_count_alpha = 0;
        Hybrid_count_beta = -5;

        Masuda_min_r2 = 3;
        Patchy_min_r2 = 3;
        Hybrid_min_r2 = 3;

        Masuda_min_N = 0;
        Patchy_min_N = 0;
        Hybrid_min_alpha = 0;
        Hybrid_min_beta = 0;

        double Masuda_r2_fit;
        double Patchy_r2_fit;
        double Hybrid_r2_fit;

        fit_count = 1;


        for(;Masuda_count_N <= 20;Masuda_count_N += 0.01)
        {


         Masuda_r2_fit = Masuda_func(Masuda_count_N,m_LineChartview->Masuda_SH_group,m_LineChartview->input_kn);

         if(Masuda_r2_fit < Masuda_min_r2)
         {
             Masuda_min_r2 = Masuda_r2_fit;
             Masuda_min_N = Masuda_count_N;
         }

        }
        m_LineChartview->Masuda_N = Masuda_min_N;
        calwidget->Masuda_N = Masuda_min_N;
        Masuda_N_edit->setText(QString::number(Masuda_min_N));



        for(;Patchy_count_N <= 15;Patchy_count_N += 0.01)
        {


         Patchy_r2_fit = Patchy_func(Patchy_count_N,m_LineChartview->Patchy_SH_group,m_LineChartview->input_kn);

         if(Patchy_r2_fit < Patchy_min_r2)
         {
             Patchy_min_r2 = Patchy_r2_fit;
             Patchy_min_N = Patchy_count_N;
         }

        }
        m_LineChartview->Patchy_N = Patchy_min_N;
        calwidget->Patchy_N = Patchy_min_N;
        Patchy_N_edit->setText(QString::number(Patchy_min_N));



        for(;Hybrid_count_alpha <= 1;Hybrid_count_alpha += 0.01)
        {
            Hybrid_count_beta = -5.0;
            for(;Hybrid_count_beta <= 30;Hybrid_count_beta += 0.01)
            {
               Hybrid_r2_fit = Hybrid_func(Hybrid_count_alpha,Hybrid_count_beta,m_LineChartview->Hybrid_SH_group,m_LineChartview->input_kn);
               if(Hybrid_r2_fit < Hybrid_min_r2)
              {
                Hybrid_min_r2 = Hybrid_r2_fit;
                Hybrid_min_alpha = Hybrid_count_alpha;
                Hybrid_min_beta = Hybrid_count_beta;
              }
            }

        }
        m_LineChartview->Hybrid_alpha = Hybrid_min_alpha;
        m_LineChartview->Hybrid_Beta = Hybrid_min_beta;
        calwidget->Hybrid_alpha = Hybrid_min_alpha;
        calwidget->Hybrid_Beta = Hybrid_min_beta;
        Hybrid_alpha_edit->setText(QString::number(Hybrid_min_alpha));
        Hybrid_Beta_edit->setText(QString::number(Hybrid_min_beta));


        m_LineChartview->calculate();

        m_LineChartview->addPointToChart_original_ver(m_LineChartview->m_Series0,m_LineChartview->input_SH,m_LineChartview->input_kn);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series1,m_LineChartview->Masuda_SH_group,m_LineChartview->Masuda_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series2,m_LineChartview->Patchy_SH_group,m_LineChartview->Patchy_kr_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series3,m_LineChartview->GC_SH_group,m_LineChartview->GC_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series4,m_LineChartview->PF_SH_group,m_LineChartview->PF_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series5,m_LineChartview->Hybrid_SH_group,m_LineChartview->Hybrid_kn_group);

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Import Data have been applied to all models. Model Data are showed on Model Axis.");

    });
    connect(FirstBox_changebtn,&QPushButton::clicked,[=](){

        m_LineChartview->Masuda_N = Masuda_N_edit->text().toDouble();
        m_LineChartview->Patchy_N = Patchy_N_edit->text().toDouble();
        m_LineChartview->Hybrid_alpha = Hybrid_alpha_edit->text().toDouble();
        m_LineChartview->Hybrid_Beta = Hybrid_Beta_edit->text().toDouble();

        calwidget->Masuda_N = Masuda_N_edit->text().toDouble();
        calwidget->Patchy_N = Patchy_N_edit->text().toDouble();
        calwidget->Hybrid_alpha = Hybrid_alpha_edit->text().toDouble();
        calwidget->Hybrid_Beta = Hybrid_Beta_edit->text().toDouble();

        m_LineChartview->calculate();

        m_LineChartview->m_Series1->clear();
        m_LineChartview->m_Series2->clear();
        m_LineChartview->m_Series3->clear();
        m_LineChartview->m_Series4->clear();
        m_LineChartview->m_Series5->clear();

        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series1,m_LineChartview->Masuda_SH_group,m_LineChartview->Masuda_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series2,m_LineChartview->Patchy_SH_group,m_LineChartview->Patchy_kr_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series3,m_LineChartview->GC_SH_group,m_LineChartview->GC_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series4,m_LineChartview->PF_SH_group,m_LineChartview->PF_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series5,m_LineChartview->Hybrid_SH_group,m_LineChartview->Hybrid_kn_group);

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Factors and Model Curves have been changed.");

    });

    connect(FirstBox_backbtn,&QPushButton::clicked,[=](){

        m_LineChartview->Masuda_N = Masuda_min_N;
        m_LineChartview->Patchy_N = Patchy_min_N;
        m_LineChartview->Hybrid_alpha = Hybrid_min_alpha;
        m_LineChartview->Hybrid_Beta = Hybrid_min_beta;

        calwidget->Masuda_N = Masuda_min_N;
        calwidget->Patchy_N = Patchy_min_N;
        calwidget->Hybrid_alpha = Hybrid_min_alpha;
        calwidget->Hybrid_Beta = Hybrid_min_beta;

        Masuda_N_edit->setText(QString::number(Masuda_min_N));
        Patchy_N_edit->setText(QString::number(Patchy_min_N));
        Hybrid_alpha_edit->setText(QString::number(Hybrid_min_alpha));
        Hybrid_Beta_edit->setText(QString::number(Hybrid_min_beta));

        m_LineChartview->calculate();

        m_LineChartview->m_Series1->clear();
        m_LineChartview->m_Series2->clear();
        m_LineChartview->m_Series3->clear();
        m_LineChartview->m_Series4->clear();
        m_LineChartview->m_Series5->clear();

        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series1,m_LineChartview->Masuda_SH_group,m_LineChartview->Masuda_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series2,m_LineChartview->Patchy_SH_group,m_LineChartview->Patchy_kr_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series3,m_LineChartview->GC_SH_group,m_LineChartview->GC_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series4,m_LineChartview->PF_SH_group,m_LineChartview->PF_kn_group);
        m_LineChartview->addPointToChart_model_ver(m_LineChartview->m_Series5,m_LineChartview->Hybrid_SH_group,m_LineChartview->Hybrid_kn_group);

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Factors and Model Curves have been initialized.");

    });


    connect(FirstBox_fittingbtn,&QPushButton::clicked,[=](){

        fitting_calculate();
        m_LineChartview->addFittingCurveToChart(m_LineChartview->fitting_Series3,m_LineChartview->fitting3_SH,m_LineChartview->fitting3_kn);
        m_LineChartview->fitting_Series3->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Cubic Polynomial Fitting has been applied to Original Data.");

    });



    QDialog *data_dialog = new QDialog(this);
    QFont set_font1("Times New Roman");

    SecondBox_starbtn = new QPushButton(data_dialog);
    SecondBox_starbtn->setText("Import - Show");
    SecondBox_starbtn->setGeometry(10,255,170,40);
    SecondBox_starbtn->setStyleSheet(this->btnstyle);

    SecondBox_combined_show_btn = new QPushButton(data_dialog);
    SecondBox_combined_show_btn->setText("Combined - Show");
    SecondBox_combined_show_btn->setGeometry(190,255,170,40);
    SecondBox_combined_show_btn->setStyleSheet(this->btnstyle);

    SecondBox_combinebtn = new QPushButton(data_dialog);
    SecondBox_combinebtn->setText("Combination");
    SecondBox_combinebtn->setGeometry(370,255,170,40);
    SecondBox_combinebtn->setStyleSheet(this->btnstyle);

    combinebox1 = new QSpinBox(data_dialog);
    QLabel *combinelabel1 = new QLabel(data_dialog);
    combinelabel1->setText("First Group(Original):");
    combinelabel1->setStyleSheet(label_str_small);
    combinelabel1->setGeometry(370,5,170,30);
    combinebox1->setGeometry(370,40,170,30);
    combinebox1->setRange(1,4);
    combinebox1->setValue(1);
    combinebox1->setWrapping(true);

    combinebox2 = new QSpinBox(data_dialog);
    QLabel *combinelabel2 = new QLabel(data_dialog);
    combinelabel2->setText("Second Group(Original):");
    combinelabel2->setStyleSheet(label_str_small);
    combinelabel2->setGeometry(370,80,170,30);
    combinebox2->setGeometry(370,120,170,30);
    combinebox2->setRange(1,4);
    combinebox2->setValue(2);
    combinebox2->setWrapping(true);
    data_dialog->setGeometry(1200,550,550,300);
    data_dialog->setFixedSize(550,300);
    data_dialog->setWindowTitle("Data Comparision and Combination");
    data_dialog->setFont(set_font1);

    connect(data_compare,&QAction::triggered,[=](){

        m_LineChartview->showlabel7->show();
        m_LineChartview->showlabel8->show();
        m_LineChartview->showlabel9->show();
        m_LineChartview->showlabel10->show();
        m_LineChartview->showlabel11->show();
        m_LineChartview->showlabel12->show();
        m_LineChartview->showlabel13->show();

        m_LineChartview->colorlabel7->show();
        m_LineChartview->colorlabel8->show();
        m_LineChartview->colorlabel9->show();
        m_LineChartview->colorlabel10->show();
        m_LineChartview->colorlabel11->show();
        m_LineChartview->colorlabel12->show();
        m_LineChartview->colorlabel13->show();

        m_LineChartview->showlabel1->hide();
        m_LineChartview->showlabel2->hide();
        m_LineChartview->showlabel3->hide();
        m_LineChartview->showlabel4->hide();
        m_LineChartview->showlabel5->hide();
        m_LineChartview->showlabel6->hide();

        m_LineChartview->colorlabel1->hide();
        m_LineChartview->colorlabel2->hide();
        m_LineChartview->colorlabel3->hide();
        m_LineChartview->colorlabel4->hide();
        m_LineChartview->colorlabel5->hide();
        m_LineChartview->colorlabel6->hide();

        m_LineChartview->setChart(m_LineChartview->m_LineChart1);
        m_LineChartview->current_chart = 1;
        createSecondBox()->setParent(data_dialog);
        createThirdBox()->setParent(data_dialog);
        data_dialog->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Shift to Data Comparision and Combination mode");

    });
    connect(SecondBox_starbtn,&QPushButton::clicked,[=](){

        m_LineChartview->addPointToChart_original_ver(m_LineChartview->input_Series0,m_LineChartview->input_SH0,m_LineChartview->input_kn0);
        m_LineChartview->addPointToChart_original_ver(m_LineChartview->input_Series1,m_LineChartview->input_SH1,m_LineChartview->input_kn1);
        m_LineChartview->addPointToChart_original_ver(m_LineChartview->input_Series2,m_LineChartview->input_SH2,m_LineChartview->input_kn2);
        m_LineChartview->addPointToChart_original_ver(m_LineChartview->input_Series3,m_LineChartview->input_SH3,m_LineChartview->input_kn3);

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Chosen Original Data have been displayed on Data Coordinate System.");

    });
    connect(SecondBox_combinebtn,&QPushButton::clicked,[=](){

        if(m_LineChartview->filled_num == 3)
        {QMessageBox::information(this,"Warning","The max number of combined group is 3.");

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Have reached the max number of combined group. Unable to run next combination.");
        }
        else{
        if(combine_num1 == combine_num2)
        {QMessageBox::information(this,"Warning","Unable to combine the same group.");

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Unable to combine the same group.");
        }
        else{

            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("The following data group(original) will be combined: ");
            status_textedit->append(QString::number(combine_num1 + 1) + " Group and" + QString::number(combine_num2 + 1) + " Group");

             for(int i=0;i<60;)
              {
                  if(m_LineChartview->input_SH_list[combine_num1][i] == 0 && m_LineChartview->input_kn_list[combine_num1][i] == 0)
                  {break;}
                  m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i] = m_LineChartview->input_SH_list[combine_num1][i];
                  m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i] = m_LineChartview->input_kn_list[combine_num1][i];
                  m_LineChartview->count_num ++;
                  i++;
              }

              for(int i=0;i<60;)
              {
                  if(m_LineChartview->input_SH_list[combine_num2][i] == 0 && m_LineChartview->input_kn_list[combine_num2][i] == 0)
                  {break;}
                  m_LineChartview->combine_SH_list[m_LineChartview->filled_num][m_LineChartview->count_num] = m_LineChartview->input_SH_list[combine_num2][i];
                  m_LineChartview->combine_kn_list[m_LineChartview->filled_num][m_LineChartview->count_num] = m_LineChartview->input_kn_list[combine_num2][i];
                  m_LineChartview->count_num ++;
                  i++;
              }

              m_LineChartview->count_num = 0;


            double temp1 = 0;
            double temp2 = 0;
            double k = 0;
            int i1 = 0;
            int small_count1 = 0;
            int small_count2 = 0;
            for(int i=0;i<120;i++)
            {

                if(m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i] ==0 && m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i] == 0)
                {break;}

                for (i1 = i + 1; i1 < 120; i1++)
                {

                    if(m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1] ==0 && m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i1] == 0)
                    {continue;}

                    if (m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i] > m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1])
                    {

                        temp1 = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1] = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i] = temp1;

                        temp2 = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i1];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i1] = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][i] = temp2;
                    }
                    if (m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i] == m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1])
                    {
                        small_count1 = i;
                        small_count2 = i1;
                        k = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i1];
                    }
                }
                if(small_count1 != 0 && k == m_LineChartview->combine_SH_list[m_LineChartview->filled_num][i])
                {
                    if (m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1] <= m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2])
                    {
                        temp1 = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count1 + 1];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count1 + 1] = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count2];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count2] = temp1;

                        temp2 = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1 + 1];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1 + 1] = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2] = temp2;
                    }else{

                        temp1 = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1] = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2] = temp1;

                        temp1 = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count1 + 1];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count1 + 1] = m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count2];
                        m_LineChartview->combine_SH_list[m_LineChartview->filled_num][small_count2] = temp1;

                        temp2 = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1 + 1];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count1 + 1] = m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2];
                        m_LineChartview->combine_kn_list[m_LineChartview->filled_num][small_count2] = temp2;
                    }
                    small_count1 = 0;
                    small_count2 = 0;
                }
                small_count1 = 0;
                small_count2 = 0;
            }

            m_LineChartview->filled_num ++;

            if(m_LineChartview->filled_num <3){
            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Chosen groups have been combined and sorted. Combined Data can be found in Statistical Table(Data).");}

            if(m_LineChartview->filled_num == 3){
            currentTime = QTime::currentTime();
            currentTime_text = currentTime.toString("hh:mm:ss");
            status_textedit->append(currentTime_text);
            status_textedit->append("Chosen groups have been combined and sorted. The number of combined groups has reached max. Combined Data can be found in Statistical Table(Data)");}
        }

        }

    });
    connect(SecondBox_combined_show_btn,&QPushButton::clicked,[=](){

        m_LineChartview->addPointToChart_combine_ver(m_LineChartview->combine_Series0,m_LineChartview->combine_SH0,m_LineChartview->combine_kn0);
        m_LineChartview->addPointToChart_combine_ver(m_LineChartview->combine_Series1,m_LineChartview->combine_SH1,m_LineChartview->combine_kn1);
        m_LineChartview->addPointToChart_combine_ver(m_LineChartview->combine_Series2,m_LineChartview->combine_SH2,m_LineChartview->combine_kn2);

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Combined Data have been displayed on Data Axis.");

    });
    connect(combinebox1, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](){

         if(combinebox1->value() == 1)
         {combine_num1 = 0;}
         if(combinebox1->value() == 2)
         {combine_num1 = 1;}
         if(combinebox1->value() == 3)
         {combine_num1 = 2;}
         if(combinebox1->value() == 4)
         {combine_num1 = 3;}

    });
    connect(combinebox2, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](){

         if(combinebox2->value() == 1)
         {combine_num2 = 0;}
         if(combinebox2->value() == 2)
         {combine_num2 = 1;}
         if(combinebox2->value() == 3)
         {combine_num2 = 2;}
         if(combinebox2->value() == 4)
         {combine_num2 = 3;}

    });

    connect(chartclear0,&QAction::triggered,[=](){

        m_LineChartview->m_Series0->clear();
        m_LineChartview->m_Series1->clear();
        m_LineChartview->m_Series2->clear();
        m_LineChartview->m_Series3->clear();
        m_LineChartview->m_Series4->clear();
        m_LineChartview->m_Series5->clear();

        fit_count = 0;

        m_LineChartview->fitting_Series3->clear();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Data groups in Model Axis have been cleared but remain in RAM. Run Model Fitting function again then all data will be displayed again. If you want to replace imported data, please reload imported file.");

    });

    connect(chartclear1,&QAction::triggered,[=](){

        m_LineChartview->input_Series0->clear();
        m_LineChartview->input_Series1->clear();
        m_LineChartview->input_Series2->clear();
        m_LineChartview->input_Series3->clear();
        m_LineChartview->input_Series4->clear();
        m_LineChartview->input_Series5->clear();
        m_LineChartview->input_Series6->clear();
        m_LineChartview->input_Series7->clear();

        m_LineChartview->combine_Series0->clear();
        m_LineChartview->combine_Series1->clear();
        m_LineChartview->combine_Series2->clear();

        m_LineChartview->filled_num = 0;
        input_file_num = 0;

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Data groups in Data Axis have been cleared but remain in RAM. Run Import - Show or Combined - Show function again then all data will be displayed again. If you want to replace imported data, please reload imported file.");

    });

    connect(status_text_clear,&QAction::triggered,[=](){

           status_textedit->clear();
    });

    connect(mark0_clear,&QAction::triggered,[=](){

           m_LineChartview->mark_Series1->clear();
           m_LineChartview->mark_Series2->clear();
           m_LineChartview->mark_Series3->clear();
           m_LineChartview->mark_Series4->clear();
           m_LineChartview->mark_Series5->clear();
           m_LineChartview->mark_Series6->clear();

           m_LineChartview->list_count = 0;

           currentTime = QTime::currentTime();
           currentTime_text = currentTime.toString("hh:mm:ss");
           status_textedit->append(currentTime_text);
           status_textedit->append("MarkLines in Model Axis have been cleared.");
    });

    connect(mark1_clear,&QAction::triggered,[=](){

           m_LineChartview->mark_Series1_->clear();
           m_LineChartview->mark_Series2_->clear();
           m_LineChartview->mark_Series3_->clear();
           m_LineChartview->mark_Series4_->clear();
           m_LineChartview->mark_Series5_->clear();
           m_LineChartview->mark_Series6_->clear();

           m_LineChartview->list_count_ = 0;

           currentTime = QTime::currentTime();
           currentTime_text = currentTime.toString("hh:mm:ss");
           status_textedit->append(currentTime_text);
           status_textedit->append("MarkLines in Data Axis have been cleared.");
    });


    QDialog *set_chart_dialog = new QDialog(this);
    QFont set_chart_font("Times New Roman");
    set_chart_dialog->setFixedSize(850,520);
    set_chart_dialog->setWindowTitle("Charts Setting");
    set_chart_dialog->setGeometry(1200,200,550,520);
    set_chart_dialog->setFont(set_chart_font);

    item_text_list.append(item_text0);
    item_text_list.append(item_text1);
    item_text_list.append(item_text2);
    item_text_list.append(item_text3);
    item_text_list.append(item_text4);
    item_text_list.append(item_text5);

    line_color_list.append(point_color0);
    line_color_list.append(line_color1);
    line_color_list.append(line_color2);
    line_color_list.append(line_color3);
    line_color_list.append(line_color4);
    line_color_list.append(line_color5);


    item_text_list_.append(item_text0_);
    item_text_list_.append(item_text1_);
    item_text_list_.append(item_text2_);
    item_text_list_.append(item_text3_);
    item_text_list_.append(item_text4_);
    item_text_list_.append(item_text5_);
    item_text_list_.append(item_text6_);

    point_color_list_.append(point_color0_);
    point_color_list_.append(point_color1_);
    point_color_list_.append(point_color2_);
    point_color_list_.append(point_color3_);
    point_color_list_.append(point_color4_);
    point_color_list_.append(point_color5_);
    point_color_list_.append(point_color6_);

    connect(set_chart,&QAction::triggered,[=](){

        createFourthBox()->setParent(set_chart_dialog);
        createFifthBox()->setParent(set_chart_dialog);
        set_chart_dialog->show();

        currentTime = QTime::currentTime();
        currentTime_text = currentTime.toString("hh:mm:ss");
        status_textedit->append(currentTime_text);
        status_textedit->append("Charts Setting");

    });




    QDialog *helpdialog = new QDialog(this);
    QTextEdit *help_textedit = new QTextEdit(helpdialog);
    QFont helptext_font("Times New Roman");
    helpdialog->setFixedSize(700,800);
    helpdialog->setWindowTitle("Document");
    help_textedit->setGeometry(10,10,680,780);
    help_textedit->setReadOnly(true);
    help_textedit->setFont(helptext_font);

    connect(output_page,&QAction::triggered,[=](){

         currentDateTime = QDateTime::currentDateTime();
         currentTime_text = currentDateTime.toString("yyyy/MM/dd/hh : mm : ss");

         QPixmap pixmap = m_LineChartview->grab();
         QString output_filepath=QFileDialog::getSaveFileName(this,tr("Save"),".",tr(" (*.png)"));
         pixmap.save(output_filepath,"png");

         currentTime = QTime::currentTime();
         currentTime_text = currentTime.toString("hh:mm:ss");
         status_textedit->append(currentTime_text);
         status_textedit->append(QString("The address of exported image is: %1").arg(output_filepath));

    });


    connect(helpfile,&QAction::triggered,[=](){

      QString path ="C:\\ALPHA MODEL\\helpfile.txt";
      QFile file(path);
      file.open(QFile::ReadOnly);
      QByteArray array =file.readAll();
      help_textedit->setText(array);
      helpdialog->show();

      currentTime = QTime::currentTime();
      currentTime_text = currentTime.toString("hh:mm:ss");
      status_textedit->append(currentTime_text);
      status_textedit->append("Search for help.");

    });


    connect(excel_example,&QAction::triggered,[=](){

       QDesktopServices::openUrl(QUrl::fromLocalFile(excel_str));

       currentTime = QTime::currentTime();
       currentTime_text = currentTime.toString("hh:mm:ss");
       status_textedit->append(currentTime_text);
       status_textedit->append("The example of file has been opened. Suggest not to modify this file.");

    });


}

QGroupBox *theapp::createFirstBox()
{
      FirstBox = new QGroupBox(tr("Displayed Models"));
      Firstgroup = new QButtonGroup(FirstBox);
      FirstBox->setGeometry(10,10,200,240);
      FirstBox->setStyleSheet(groupstyle);
      modelbox0 = new QCheckBox(tr("Original Data"),FirstBox);
      modelbox1 = new QCheckBox(tr("Tokyo model"),FirstBox);
      modelbox2 = new QCheckBox(tr("Patchy model"),FirstBox);
      modelbox3 = new QCheckBox(tr("G-C model"),FirstBox);
      modelbox4 = new QCheckBox(tr("P-F model"),FirstBox);
      modelbox5 = new QCheckBox(tr("Hybrid model"),FirstBox);

      Firstgroup->setExclusive(false);

      modelbox0->setGeometry(10,30,180,30);
      modelbox1->setGeometry(10,60,180,30);
      modelbox2->setGeometry(10,90,180,30);
      modelbox3->setGeometry(10,120,180,30);
      modelbox4->setGeometry(10,150,180,30);
      modelbox5->setGeometry(10,180,180,30);

      modelbox0->setCheckState(Qt::Checked);
      modelbox1->setCheckState(Qt::Checked);
      modelbox2->setCheckState(Qt::Checked);
      modelbox3->setCheckState(Qt::Checked);
      modelbox4->setCheckState(Qt::Checked);
      modelbox5->setCheckState(Qt::Checked);

      modelbox0->setStyleSheet(checkboxstyle);
      modelbox1->setStyleSheet(checkboxstyle);
      modelbox2->setStyleSheet(checkboxstyle);
      modelbox3->setStyleSheet(checkboxstyle);
      modelbox4->setStyleSheet(checkboxstyle);
      modelbox5->setStyleSheet(checkboxstyle);

      Firstgroup->addButton(modelbox0);
      Firstgroup->addButton(modelbox1);
      Firstgroup->addButton(modelbox2);
      Firstgroup->addButton(modelbox3);
      Firstgroup->addButton(modelbox4);
      Firstgroup->addButton(modelbox5);


      connect(Firstgroup, static_cast<void(QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
            [=](){

          m_LineChartview->m_LineChart->setAnimationOptions(QChart::NoAnimation);
          if(modelbox0->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series0->setVisible(false);}
          else if(modelbox0->checkState() == Qt::Checked)
          {m_LineChartview->m_Series0->setVisible(true);}

          if(modelbox1->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series1->setVisible(false);}
          else if(modelbox1->checkState() == Qt::Checked)
          {m_LineChartview->m_Series1->setVisible(true);}

          if(modelbox2->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series2->setVisible(false);}
          else if(modelbox2->checkState() == Qt::Checked)
          {m_LineChartview->m_Series2->setVisible(true);}

          if(modelbox3->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series3->setVisible(false);}
          else if(modelbox3->checkState() == Qt::Checked)
          {m_LineChartview->m_Series3->setVisible(true);}

          if(modelbox4->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series4->setVisible(false);}
          else if(modelbox4->checkState() == Qt::Checked)
          {m_LineChartview->m_Series4->setVisible(true);}

          if(modelbox5->checkState() == Qt::Unchecked)
          {m_LineChartview->m_Series5->setVisible(false);}
          else if(modelbox5->checkState() == Qt::Checked)
          {m_LineChartview->m_Series5->setVisible(true);}

      });

      return FirstBox;
}
QGroupBox *theapp::createSixthBox()
{
      SixthBox = new QGroupBox(tr("Factors(Masuda)"));
      SixthBox->setGeometry(220,10,185,110);
      SixthBox->setStyleSheet(groupstyle);

      QLabel *Masuda_N_label = new QLabel(SixthBox);
      Masuda_N_label->setText("n:");
      Masuda_N_label->setGeometry(10,30,40,25);
      Masuda_N_label->setStyleSheet(label_str);

      Masuda_N_edit = new QLineEdit(SixthBox);
      Masuda_N_edit->setGeometry(50,30,80,25);
      Masuda_N_edit->setText(QString::number(Masuda_min_N));
      Masuda_N_edit->setStyleSheet(lineedit_str);

      return SixthBox;
}
QGroupBox *theapp::create7thBox()
{
      _7thBox = new QGroupBox(tr("Factors(Patchy)"));
      _7thBox->setGeometry(410,10,185,110);
      _7thBox->setStyleSheet(groupstyle);

      QLabel *Patchy_N_label = new QLabel(_7thBox);
      Patchy_N_label->setText("n:");
      Patchy_N_label->setGeometry(10,30,40,25);
      Patchy_N_label->setStyleSheet(label_str);

      Patchy_N_edit = new QLineEdit(_7thBox);
      Patchy_N_edit->setGeometry(50,30,80,25);
      Patchy_N_edit->setText(QString::number(Patchy_min_N));
      Patchy_N_edit->setStyleSheet(lineedit_str);

      return _7thBox;
}
QGroupBox *theapp::create8thBox()
{
      _8thBox = new QGroupBox(tr("Factors(Hybrid)"));
      _8thBox->setGeometry(220,130,185,110);
      _8thBox->setStyleSheet(groupstyle);

      QLabel *Hybrid_alpha_label = new QLabel(_8thBox);
      Hybrid_alpha_label->setText("α:");
      Hybrid_alpha_label->setGeometry(10,30,40,25);
      Hybrid_alpha_label->setStyleSheet(label_str);

      Hybrid_alpha_edit = new QLineEdit(_8thBox);
      Hybrid_alpha_edit->setGeometry(50,30,80,25);
      Hybrid_alpha_edit->setText(QString::number(Hybrid_min_alpha));
      Hybrid_alpha_edit->setStyleSheet(lineedit_str);

      QLabel *Hybrid_Beta_label = new QLabel(_8thBox);
      Hybrid_Beta_label->setText("β:");
      Hybrid_Beta_label->setGeometry(10,65,40,25);
      Hybrid_Beta_label->setStyleSheet(label_str);

      Hybrid_Beta_edit = new QLineEdit(_8thBox);
      Hybrid_Beta_edit->setGeometry(50,65,80,25);
      Hybrid_Beta_edit->setText(QString::number(Hybrid_min_beta));
      Hybrid_Beta_edit->setStyleSheet(lineedit_str);

      return _8thBox;
}

QGroupBox *theapp::createSecondBox()
{
      SecondBox = new QGroupBox(tr("Original Data"));
      Secondgroup = new QButtonGroup(SecondBox);
      SecondBox->setGeometry(10,10,165,240);
      SecondBox->setStyleSheet(groupstyle);
      input_box0 = new QCheckBox(tr("Original Data 1"),SecondBox);
      input_box1 = new QCheckBox(tr("Original Data 2"),SecondBox);
      input_box2 = new QCheckBox(tr("Original Data 3"),SecondBox);
      input_box3 = new QCheckBox(tr("Original Data 4"),SecondBox);

      Secondgroup->setExclusive(false);

      input_box0->setGeometry(10,30,170,30);
      input_box1->setGeometry(10,60,170,30);
      input_box2->setGeometry(10,90,170,30);
      input_box3->setGeometry(10,120,170,30);

      input_box0->setCheckState(Qt::Checked);
      input_box1->setCheckState(Qt::Checked);
      input_box2->setCheckState(Qt::Checked);
      input_box3->setCheckState(Qt::Checked);

      input_box0->setStyleSheet(checkboxstyle);
      input_box1->setStyleSheet(checkboxstyle);
      input_box2->setStyleSheet(checkboxstyle);
      input_box3->setStyleSheet(checkboxstyle);

      Secondgroup->addButton(input_box0);
      Secondgroup->addButton(input_box1);
      Secondgroup->addButton(input_box2);
      Secondgroup->addButton(input_box3);

      connect(Secondgroup, static_cast<void(QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
            [=](){

          m_LineChartview->m_LineChart1->setAnimationOptions(QChart::NoAnimation);
          if(input_box0->checkState() == Qt::Unchecked)
          {m_LineChartview->input_Series0->setVisible(false);}
          else if(input_box0->checkState() == Qt::Checked)
          {m_LineChartview->input_Series0->setVisible(true);}

          if(input_box1->checkState() == Qt::Unchecked)
          {m_LineChartview->input_Series1->setVisible(false);}
          else if(input_box1->checkState() == Qt::Checked)
          {m_LineChartview->input_Series1->setVisible(true);}

          if(input_box2->checkState() == Qt::Unchecked)
          {m_LineChartview->input_Series2->setVisible(false);}
          else if(input_box2->checkState() == Qt::Checked)
          {m_LineChartview->input_Series2->setVisible(true);}

          if(input_box3->checkState() == Qt::Unchecked)
          {m_LineChartview->input_Series3->setVisible(false);}
          else if(input_box3->checkState() == Qt::Checked)
          {m_LineChartview->input_Series3->setVisible(true);}
          m_LineChartview->m_LineChart1->setAnimationOptions(QChart::AllAnimations);
      });

      return SecondBox;
}
QGroupBox *theapp::createThirdBox()
{
      ThirdBox = new QGroupBox(tr("Combined Data"));
      Thirdgroup = new QButtonGroup(ThirdBox);
      ThirdBox->setGeometry(185,10,180,240);
      ThirdBox->setStyleSheet(groupstyle);
      combined_box0 = new QCheckBox(tr("Combined Data 1"),ThirdBox);
      combined_box1 = new QCheckBox(tr("Combined Data 2"),ThirdBox);
      combined_box2 = new QCheckBox(tr("Combined Data 3"),ThirdBox);

      Thirdgroup->setExclusive(false);

      combined_box0->setGeometry(10,30,180,30);
      combined_box1->setGeometry(10,60,180,30);
      combined_box2->setGeometry(10,90,180,30);

      combined_box0->setCheckState(Qt::Checked);
      combined_box1->setCheckState(Qt::Checked);
      combined_box2->setCheckState(Qt::Checked);

      combined_box0->setStyleSheet(checkboxstyle);
      combined_box1->setStyleSheet(checkboxstyle);
      combined_box2->setStyleSheet(checkboxstyle);

      Thirdgroup->addButton(combined_box0);
      Thirdgroup->addButton(combined_box1);
      Thirdgroup->addButton(combined_box2);


      connect(Thirdgroup, static_cast<void(QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
            [=](){

          m_LineChartview->m_LineChart1->setAnimationOptions(QChart::NoAnimation);
          if(combined_box0->checkState() == Qt::Unchecked)
          {m_LineChartview->combine_Series0->setVisible(false);}
          else if(combined_box0->checkState() == Qt::Checked)
          {m_LineChartview->combine_Series0->setVisible(true);}

          if(combined_box1->checkState() == Qt::Unchecked)
          {m_LineChartview->combine_Series1->setVisible(false);}
          else if(combined_box1->checkState() == Qt::Checked)
          {m_LineChartview->combine_Series1->setVisible(true);}

          if(combined_box2->checkState() == Qt::Unchecked)
          {m_LineChartview->combine_Series2->setVisible(false);}
          else if(combined_box2->checkState() == Qt::Checked)
          {m_LineChartview->combine_Series2->setVisible(true);}

          m_LineChartview->m_LineChart1->setAnimationOptions(QChart::AllAnimations);

      });

      return ThirdBox;
}
QGroupBox *theapp::createFourthBox()
{
      FourthBox = new QGroupBox(tr("Model Coordinate System"));
      FourthBox->setGeometry(10,10,405,500);
      FourthBox->setStyleSheet(groupstyle);

      QLabel *x_name_label = new QLabel(FourthBox);
      x_name_label->setText("Name(X)");
      x_name_label->setGeometry(20,25,100,40);
      x_name_label->setStyleSheet(label_str);

      x_name = new QLineEdit(FourthBox);
      x_name->setGeometry(120,25,275,40);
      x_name->setStyleSheet(lineedit_str);
      x_name->setText(x_name_text);

      QLabel *x_range_label1 = new QLabel(FourthBox);
      x_range_label1->setText("X Range: From");
      x_range_label1->setGeometry(20,70,140,40);
      x_range_label1->setStyleSheet(label_str);

      x_range1 = new QLineEdit(FourthBox);
      x_range1->setGeometry(165,70,100,40);
      x_range1->setStyleSheet(lineedit_str);
      x_range1->setText(x_range1_text);

      QLabel *x_range_label2 = new QLabel(FourthBox);
      x_range_label2->setText("To");
      x_range_label2->setGeometry(270,70,25,40);
      x_range_label2->setStyleSheet(label_str);

      x_range2 = new QLineEdit(FourthBox);
      x_range2->setGeometry(300,70,95,40);
      x_range2->setStyleSheet(lineedit_str);
      x_range2->setText(x_range2_text);

      QLabel *y_name_label = new QLabel(FourthBox);
      y_name_label->setText("Name(Y)");
      y_name_label->setGeometry(20,115,100,40);
      y_name_label->setStyleSheet(label_str);

      y_name = new QLineEdit(FourthBox);
      y_name->setGeometry(120,115,275,40);
      y_name->setStyleSheet(lineedit_str);
      y_name->setText(y_name_text);

      QLabel *y_range_label1 = new QLabel(FourthBox);
      y_range_label1->setText("Y Range: From");
      y_range_label1->setGeometry(20,160,140,40);
      y_range_label1->setStyleSheet(label_str);

      y_range1 = new QLineEdit(FourthBox);
      y_range1->setGeometry(170,160,95,40);
      y_range1->setStyleSheet(lineedit_str);
      y_range1->setText(y_range1_text);

      QLabel *y_range_label2 = new QLabel(FourthBox);
      y_range_label2->setText("To");
      y_range_label2->setGeometry(270,160,25,40);
      y_range_label2->setStyleSheet(label_str);

      y_range2 = new QLineEdit(FourthBox);
      y_range2->setGeometry(300,160,95,40);
      y_range2->setStyleSheet(lineedit_str);
      y_range2->setText("1");

      QLabel *chart_name = new QLabel(FourthBox);
      chart_name->setText("Name of Axis");
      chart_name->setGeometry(20,205,125,40);
      chart_name->setStyleSheet(label_str);

      title = new QLineEdit(FourthBox);
      title->setGeometry(150,205,245,40);
      title->setStyleSheet(lineedit_str);
      title->setText(title_text);

      QLabel *legend_name = new QLabel(FourthBox);
      legend_name->setText("Name of legend");
      legend_name->setGeometry(20,250,150,40);
      legend_name->setStyleSheet(label_str);

      legendBox = new QComboBox(FourthBox);
      legendBox->setGeometry(175,250,135,40);
      legendedit = new QLineEdit(FourthBox);
      legendBox->setLineEdit(legendedit);
      legendBox->insertItem(0,item_text_list[0]);
      legendBox->insertItem(1,item_text_list[1]);
      legendBox->insertItem(2,item_text_list[2]);
      legendBox->insertItem(3,item_text_list[3]);
      legendBox->insertItem(4,item_text_list[4]);
      legendBox->insertItem(5,item_text_list[5]);

      legend_savebtn = new QPushButton(FourthBox);
      legend_savebtn->setText("OK");
      legend_savebtn->setGeometry(315,250,80,40);
      legend_savebtn->setStyleSheet(this->btnstyle);

      QLabel *data_color = new QLabel(FourthBox);
      data_color->setText("Data Color");
      data_color->setGeometry(20,295,100,40);
      data_color->setStyleSheet(label_str);

      datacolorBox = new QComboBox(FourthBox);
      datacolorBox->setGeometry(125,295,185,40);
      datacolorBox->insertItem(0,item_text_list[0]);
      datacolorBox->insertItem(1,item_text_list[1]);
      datacolorBox->insertItem(2,item_text_list[2]);
      datacolorBox->insertItem(3,item_text_list[3]);
      datacolorBox->insertItem(4,item_text_list[4]);
      datacolorBox->insertItem(5,item_text_list[5]);

      color_savebtn1 = new QPushButton(FourthBox);
      color_savebtn1->setText("Choose");
      color_savebtn1->setGeometry(315,295,80,40);
      color_savebtn1->setStyleSheet(this->btnstyle);

      QLabel *point_size = new QLabel(FourthBox);
      point_size->setText("Data Size");
      point_size->setGeometry(20,340,100,40);
      point_size->setStyleSheet(label_str);

      sizebox = new QSpinBox(FourthBox);
      sizebox->setGeometry(125,340,185,40);
      sizebox->setRange(3,20);
      sizebox->setValue(size);
      sizebox->setWrapping(true);

      size_savebtn = new QPushButton(FourthBox);
      size_savebtn->setText("OK");
      size_savebtn->setGeometry(315,340,80,40);
      size_savebtn->setStyleSheet(this->btnstyle);

      QLabel *chartview_color = new QLabel(FourthBox);
      chartview_color->setText("Background Color");
      chartview_color->setGeometry(20,385,170,40);
      chartview_color->setStyleSheet(label_str);

      color_savebtn2 = new QPushButton(FourthBox);
      color_savebtn2->setText("Choose");
      color_savebtn2->setGeometry(295,385,100,40);
      color_savebtn2->setStyleSheet(this->btnstyle);

      savebtn1 = new QPushButton(FourthBox);
      savebtn1->setText("Save");
      savebtn1->setGeometry(25,440,130,40);
      savebtn1->setStyleSheet(this->btnstyle);

      setbackbtn1 = new QPushButton(FourthBox);
      setbackbtn1->setText("Initialization");
      setbackbtn1->setGeometry(250,440,130,40);
      setbackbtn1->setStyleSheet(this->btnstyle);

      connect(color_savebtn1,&QPushButton::clicked,[=](){

          line_color_list[datacolorBox->currentIndex()] = QColorDialog::getColor(Qt::black,this,"Chose Color",QColorDialog::ShowAlphaChannel);

      });


      connect(size_savebtn,&QPushButton::clicked,[=](){

          size = sizebox->value();

      });


      connect(color_savebtn2,&QPushButton::clicked,[=](){

          chartcolor = QColorDialog::getColor(Qt::white,this,"Chose Color",QColorDialog::ShowAlphaChannel);

      });

      connect(legend_savebtn,&QPushButton::clicked,[=](){

          legendBox->setItemText(legendBox->currentIndex(),legendedit->text());
          item_text_list[legendBox->currentIndex()] = legendedit->text();

      });


      connect(savebtn1,&QPushButton::clicked,[=](){

          QFont xyFont_1("Arial", 12, QFont::Bold);
          m_LineChartview->m_AxisX->setTitleText(x_name->text());
          m_LineChartview->m_AxisX->setTitleFont(xyFont_1);
          x_name_text = x_name->text();

          m_LineChartview->m_AxisX->setRange(x_range1->text().toDouble(),x_range2->text().toDouble());
          x_range1_text = x_range1->text();
          x_range2_text = x_range2->text();

          m_LineChartview->m_AxisY->setTitleText(y_name->text());
          m_LineChartview->m_AxisY->setTitleFont(xyFont_1);
          y_name_text = y_name->text();

          m_LineChartview->m_AxisY->setRange(y_range1->text().toDouble(),y_range2->text().toDouble());
          y_range1_text = y_range1->text();
          y_range2_text = y_range2->text();

          QFont TitleFont_1("Arial", 15, QFont::Bold);
          m_LineChartview->m_LineChart->setTitle(title->text());
          m_LineChartview->m_LineChart->setTitleFont(TitleFont_1);
          title_text = title->text();

          m_LineChartview->m_Series0->setName(item_text_list[0]);
          m_LineChartview->m_Series1->setName(item_text_list[1]);
          m_LineChartview->m_Series2->setName(item_text_list[2]);
          m_LineChartview->m_Series3->setName(item_text_list[3]);
          m_LineChartview->m_Series4->setName(item_text_list[4]);
          m_LineChartview->m_Series5->setName(item_text_list[5]);

          m_LineChartview->showlabel1->setText(item_text_list[0]);
          m_LineChartview->showlabel2->setText(item_text_list[1]);
          m_LineChartview->showlabel3->setText(item_text_list[2]);
          m_LineChartview->showlabel4->setText(item_text_list[3]);
          m_LineChartview->showlabel5->setText(item_text_list[4]);
          m_LineChartview->showlabel6->setText(item_text_list[5]);


          m_LineChartview->m_Series0->setBrush(line_color_list[0]);
          m_LineChartview->m_Series0->setBorderColor(line_color_list[0]);

          m_LineChartview->pe1.setColor(QPalette::Background,line_color_list[0]);
          m_LineChartview->colorlabel1->setPalette(m_LineChartview->pe1);

          m_LineChartview->m_Series1_pen.setColor(line_color_list[1]);
          m_LineChartview->m_Series1->setPen(m_LineChartview->m_Series1_pen);

          m_LineChartview->pe2.setColor(QPalette::Background,line_color_list[1]);
          m_LineChartview->colorlabel2->setPalette(m_LineChartview->pe2);

          m_LineChartview->m_Series2_pen.setColor(line_color_list[2]);
          m_LineChartview->m_Series2->setPen(m_LineChartview->m_Series2_pen);

          m_LineChartview->pe3.setColor(QPalette::Background,line_color_list[2]);
          m_LineChartview->colorlabel3->setPalette(m_LineChartview->pe3);

          m_LineChartview->m_Series3_pen.setColor(line_color_list[3]);
          m_LineChartview->m_Series3->setPen(m_LineChartview->m_Series3_pen);

          m_LineChartview->pe4.setColor(QPalette::Background,line_color_list[3]);
          m_LineChartview->colorlabel4->setPalette(m_LineChartview->pe4);

          m_LineChartview->m_Series4_pen.setColor(line_color_list[4]);
          m_LineChartview->m_Series4->setPen(m_LineChartview->m_Series4_pen);

          m_LineChartview->pe5.setColor(QPalette::Background,line_color_list[4]);
          m_LineChartview->colorlabel5->setPalette(m_LineChartview->pe5);

          m_LineChartview->m_Series5_pen.setColor(line_color_list[5]);
          m_LineChartview->m_Series5->setPen(m_LineChartview->m_Series5_pen);

          m_LineChartview->pe6.setColor(QPalette::Background,line_color_list[5]);
          m_LineChartview->colorlabel6->setPalette(m_LineChartview->pe6);


          m_LineChartview->m_Series0->setMarkerSize(size_point);

          m_LineChartview->m_Series1_pen.setWidth(size);
          m_LineChartview->m_Series1->setPen(m_LineChartview->m_Series1_pen);

          m_LineChartview->m_Series2_pen.setWidth(size);
          m_LineChartview->m_Series2->setPen(m_LineChartview->m_Series2_pen);

          m_LineChartview->m_Series3_pen.setWidth(size);
          m_LineChartview->m_Series3->setPen(m_LineChartview->m_Series3_pen);

          m_LineChartview->m_Series4_pen.setWidth(size);
          m_LineChartview->m_Series4->setPen(m_LineChartview->m_Series4_pen);

          m_LineChartview->m_Series5_pen.setWidth(size);
          m_LineChartview->m_Series5->setPen(m_LineChartview->m_Series5_pen);


          m_LineChartview->m_LineChart->setBackgroundBrush(chartcolor);

      });

      connect(setbackbtn1,&QPushButton::clicked,[=](){

          m_LineChartview->m_AxisX->setTitleText(strText_x_axis);
          x_name->setText("Saturation");
          x_name_text = "Saturation";

          m_LineChartview->m_AxisX->setRange(0,0.5);
          x_range1->setText("0");
          x_range2->setText("0.5");
          x_range1_text = "0";
          x_range2_text = "0.5";

          m_LineChartview->m_AxisY->setTitleText(strText_y_axis);
          y_name->setText("Permeability");
          y_name_text = "Permeability";

          m_LineChartview->m_AxisY->setRange(0,1);
          y_range1->setText("0");
          y_range2->setText("1");
          y_range1_text = "0";
          y_range2_text = "1";

          m_LineChartview->m_LineChart->setTitle(strText);
          title->setText(Chartname);
          title_text = Chartname;

          m_LineChartview->m_Series0->setName("Original Data");
          m_LineChartview->m_Series1->setName("Tokyo model");
          m_LineChartview->m_Series2->setName("Patchy model");
          m_LineChartview->m_Series3->setName("G-C model");
          m_LineChartview->m_Series4->setName("P-F model");
          m_LineChartview->m_Series5->setName("Hybrid model");

          m_LineChartview->showlabel1->setText("Original Data");
          m_LineChartview->showlabel2->setText("Tokyo model");
          m_LineChartview->showlabel3->setText("Patchy model");
          m_LineChartview->showlabel4->setText("G-C model");
          m_LineChartview->showlabel5->setText("P-F model");
          m_LineChartview->showlabel6->setText("Hybrid model");

          item_text_list[0] = "Original Data";
          item_text_list[1] = "Tokyo model";
          item_text_list[2] = "Patchy model";
          item_text_list[3] = "G-C model";
          item_text_list[4] = "P-F model";
          item_text_list[5] = "Hybrid model";

          legendBox->setItemText(0,"Original Data");
          legendBox->setItemText(1,"Tokyo model");
          legendBox->setItemText(2,"Patchy model");
          legendBox->setItemText(3,"G-C model");
          legendBox->setItemText(4,"P-F model");
          legendBox->setItemText(5,"Hybrid model");


          m_LineChartview->m_Series0->setBrush(Qt::black);
          m_LineChartview->m_Series0->setBorderColor(Qt::black);
          line_color_list[0] = Qt::black;
          m_LineChartview->pe1.setColor(QPalette::Background,line_color_list[0]);
          m_LineChartview->colorlabel1->setPalette(m_LineChartview->pe1);

          m_LineChartview->m_Series1_pen.setColor(QColor(255,140,0));
          line_color_list[1] = QColor(255,140,0);
          m_LineChartview->pe2.setColor(QPalette::Background,line_color_list[1]);
          m_LineChartview->colorlabel2->setPalette(m_LineChartview->pe2);

          m_LineChartview->m_Series2_pen.setColor(QColor(60,179,113));
          line_color_list[2] = QColor(60,179,113);
          m_LineChartview->pe3.setColor(QPalette::Background,line_color_list[2]);
          m_LineChartview->colorlabel3->setPalette(m_LineChartview->pe3);

          m_LineChartview->m_Series3_pen.setColor(QColor(72,61,139));
          line_color_list[3] = QColor(72,61,139);
          m_LineChartview->pe4.setColor(QPalette::Background,line_color_list[3]);
          m_LineChartview->colorlabel4->setPalette(m_LineChartview->pe4);

          m_LineChartview->m_Series4_pen.setColor(QColor(148,0,211));
          line_color_list[4] = QColor(148,0,211);
          m_LineChartview->pe5.setColor(QPalette::Background,line_color_list[4]);
          m_LineChartview->colorlabel5->setPalette(m_LineChartview->pe5);

          m_LineChartview->m_Series5_pen.setColor(QColor(30,144,255));
          line_color_list[5] = QColor(30,144,255);
          m_LineChartview->pe6.setColor(QPalette::Background,line_color_list[5]);
          m_LineChartview->colorlabel6->setPalette(m_LineChartview->pe6);


          size = 4;
          size_point = 8;
          m_LineChartview->m_Series0->setMarkerSize(size_point);

          m_LineChartview->m_Series1_pen.setWidth(size);
          m_LineChartview->m_Series1->setPen(m_LineChartview->m_Series1_pen);

          m_LineChartview->m_Series2_pen.setWidth(size);
          m_LineChartview->m_Series2->setPen(m_LineChartview->m_Series2_pen);

          m_LineChartview->m_Series3_pen.setWidth(size);
          m_LineChartview->m_Series3->setPen(m_LineChartview->m_Series3_pen);

          m_LineChartview->m_Series4_pen.setWidth(size);
          m_LineChartview->m_Series4->setPen(m_LineChartview->m_Series4_pen);

          m_LineChartview->m_Series5_pen.setWidth(size);
          m_LineChartview->m_Series5->setPen(m_LineChartview->m_Series5_pen);


          chartcolor = Qt::white;
          m_LineChartview->m_LineChart->setBackgroundBrush(Qt::white);

      });

      return FourthBox;
}
QGroupBox *theapp::createFifthBox()
{
      FifthBox = new QGroupBox(tr("Data Coordinate System"));
      FifthBox->setGeometry(435,10,405,500);
      FifthBox->setStyleSheet(groupstyle);


      QLabel *x_name_label = new QLabel(FifthBox);
      x_name_label->setText("Name(X)");
      x_name_label->setGeometry(20,25,100,40);
      x_name_label->setStyleSheet(label_str);

      x_name_ = new QLineEdit(FifthBox);
      x_name_->setGeometry(120,25,275,40);
      x_name_->setStyleSheet(lineedit_str);
      x_name_->setText(x_name_text_);

      QLabel *x_range_label1 = new QLabel(FifthBox);
      x_range_label1->setText("X Range: From");
      x_range_label1->setGeometry(20,70,140,40);
      x_range_label1->setStyleSheet(label_str);

      x_range1_ = new QLineEdit(FifthBox);
      x_range1_->setGeometry(165,70,100,40);
      x_range1_->setStyleSheet(lineedit_str);
      x_range1_->setText(x_range1_text_);

      QLabel *x_range_label2 = new QLabel(FifthBox);
      x_range_label2->setText("To");
      x_range_label2->setGeometry(270,70,25,40);
      x_range_label2->setStyleSheet(label_str);

      x_range2_ = new QLineEdit(FifthBox);
      x_range2_->setGeometry(300,70,95,40);
      x_range2_->setStyleSheet(lineedit_str);
      x_range2_->setText(x_range2_text_);


      QLabel *y_name_label = new QLabel(FifthBox);
      y_name_label->setText("Name(Y)");
      y_name_label->setGeometry(20,115,100,40);
      y_name_label->setStyleSheet(label_str);

      y_name_ = new QLineEdit(FifthBox);
      y_name_->setGeometry(120,115,275,40);
      y_name_->setStyleSheet(lineedit_str);
      y_name_->setText(y_name_text_);

      QLabel *y_range_label1 = new QLabel(FifthBox);
      y_range_label1->setText("Y Range: From");
      y_range_label1->setGeometry(20,160,140,40);
      y_range_label1->setStyleSheet(label_str);

      y_range1_ = new QLineEdit(FifthBox);
      y_range1_->setGeometry(170,160,95,40);
      y_range1_->setStyleSheet(lineedit_str);
      y_range1_->setText(y_range1_text_);

      QLabel *y_range_label2 = new QLabel(FifthBox);
      y_range_label2->setText("To");
      y_range_label2->setGeometry(270,160,25,40);
      y_range_label2->setStyleSheet(label_str);

      y_range2_ = new QLineEdit(FifthBox);
      y_range2_->setGeometry(300,160,95,40);
      y_range2_->setStyleSheet(lineedit_str);
      y_range2_->setText("1");

      QLabel *chart_name = new QLabel(FifthBox);
      chart_name->setText("Name of Axis");
      chart_name->setGeometry(20,205,125,40);
      chart_name->setStyleSheet(label_str);

      title_ = new QLineEdit(FifthBox);
      title_->setGeometry(150,205,245,40);
      title_->setStyleSheet(lineedit_str);
      title_->setText(title_text_);

      QLabel *legend_name = new QLabel(FifthBox);
      legend_name->setText("Name of legend");
      legend_name->setGeometry(20,250,150,40);
      legend_name->setStyleSheet(label_str);

      legendBox_ = new QComboBox(FifthBox);
      legendBox_->setGeometry(175,250,135,40);
      legendedit_ = new QLineEdit(FifthBox);
      legendBox_->setLineEdit(legendedit_);
      legendBox_->insertItem(0,item_text_list_[0]);
      legendBox_->insertItem(1,item_text_list_[1]);
      legendBox_->insertItem(2,item_text_list_[2]);
      legendBox_->insertItem(3,item_text_list_[3]);
      legendBox_->insertItem(4,item_text_list_[4]);
      legendBox_->insertItem(5,item_text_list_[5]);
      legendBox_->insertItem(6,item_text_list_[6]);

      legend_savebtn_ = new QPushButton(FifthBox);
      legend_savebtn_->setText("OK");
      legend_savebtn_->setGeometry(315,250,80,40);
      legend_savebtn_->setStyleSheet(this->btnstyle);

      QLabel *data_color = new QLabel(FifthBox);
      data_color->setText("Data Color");
      data_color->setGeometry(20,295,100,40);
      data_color->setStyleSheet(label_str);

      datacolorBox_ = new QComboBox(FifthBox);
      datacolorBox_->setGeometry(125,295,185,40);
      datacolorBox_->insertItem(0,item_text_list_[0]);
      datacolorBox_->insertItem(1,item_text_list_[1]);
      datacolorBox_->insertItem(2,item_text_list_[2]);
      datacolorBox_->insertItem(3,item_text_list_[3]);
      datacolorBox_->insertItem(4,item_text_list_[4]);
      datacolorBox_->insertItem(5,item_text_list_[5]);
      datacolorBox_->insertItem(6,item_text_list_[6]);

      color_savebtn1_ = new QPushButton(FifthBox);
      color_savebtn1_->setText("Choose");
      color_savebtn1_->setGeometry(315,295,80,40);
      color_savebtn1_->setStyleSheet(this->btnstyle);

      QLabel *point_size = new QLabel(FifthBox);
      point_size->setText("Data Size");
      point_size->setGeometry(20,340,100,40);
      point_size->setStyleSheet(label_str);

      sizebox_ = new QSpinBox(FifthBox);
      sizebox_->setGeometry(125,340,185,40);
      sizebox_->setRange(3,20);
      sizebox_->setValue(size_);
      sizebox_->setWrapping(true);

      size_savebtn_ = new QPushButton(FifthBox);
      size_savebtn_->setText("OK");
      size_savebtn_->setGeometry(315,340,80,40);
      size_savebtn_->setStyleSheet(this->btnstyle);

      QLabel *chartview_color = new QLabel(FifthBox);
      chartview_color->setText("Background Color");
      chartview_color->setGeometry(20,385,170,40);
      chartview_color->setStyleSheet(label_str);

      color_savebtn2_ = new QPushButton(FifthBox);
      color_savebtn2_->setText("Choose");
      color_savebtn2_->setGeometry(295,385,100,40);
      color_savebtn2_->setStyleSheet(this->btnstyle);

      savebtn2 = new QPushButton(FifthBox);
      savebtn2->setText("Save");
      savebtn2->setGeometry(25,440,130,40);
      savebtn2->setStyleSheet(this->btnstyle);

      setbackbtn2 = new QPushButton(FifthBox);
      setbackbtn2->setText("Initialization");
      setbackbtn2->setGeometry(250,440,130,40);
      setbackbtn2->setStyleSheet(this->btnstyle);


      connect(color_savebtn1_,&QPushButton::clicked,[=](){

          point_color_list_[datacolorBox_->currentIndex()] = QColorDialog::getColor(Qt::black,this,"Choose Color",QColorDialog::ShowAlphaChannel);

      });


      connect(size_savebtn_,&QPushButton::clicked,[=](){

          size_ = sizebox_->value();
          size_point = size_;

      });


      connect(color_savebtn2_,&QPushButton::clicked,[=](){

          chartcolor_ = QColorDialog::getColor(Qt::white,this,"Choose Color",QColorDialog::ShowAlphaChannel);

      });


      connect(legend_savebtn_,&QPushButton::clicked,[=](){

          legendBox_->setItemText(legendBox_->currentIndex(),legendedit_->text());
          item_text_list_[legendBox_->currentIndex()] = legendedit_->text();

      });


      connect(savebtn2,&QPushButton::clicked,[=](){

          m_LineChartview->m_AxisX1->setTitleText(x_name_->text());
          QFont xyFont_2("Arial", 12, QFont::Bold);
          m_LineChartview->m_AxisX1->setTitleFont(xyFont_2);
          x_name_text_ = x_name_->text();

          m_LineChartview->m_AxisX1->setRange(x_range1_->text().toDouble(),x_range2_->text().toDouble());
          x_range1_text_ = x_range1_->text();
          x_range2_text_ = x_range2_->text();

          m_LineChartview->m_AxisY1->setTitleText(y_name_->text());
          m_LineChartview->m_AxisY1->setTitleFont(xyFont_2);
          y_name_text_ = y_name_->text();

          m_LineChartview->m_AxisY1->setRange(y_range1_->text().toDouble(),y_range2_->text().toDouble());
          y_range1_text_ = y_range1_->text();
          y_range2_text_ = y_range2_->text();

          QFont TitleFont_2("Arial", 15, QFont::Bold);
          m_LineChartview->m_LineChart1->setTitle(title_->text());
          m_LineChartview->m_LineChart1->setTitleFont(TitleFont_2);
          title_text_ = title_->text();

          m_LineChartview->input_Series0->setName(item_text_list_[0]);
          m_LineChartview->input_Series1->setName(item_text_list_[1]);
          m_LineChartview->input_Series2->setName(item_text_list_[2]);
          m_LineChartview->input_Series3->setName(item_text_list_[3]);
          m_LineChartview->combine_Series0->setName(item_text_list_[4]);
          m_LineChartview->combine_Series1->setName(item_text_list_[5]);
          m_LineChartview->combine_Series2->setName(item_text_list_[6]);

          m_LineChartview->showlabel7->setText(item_text_list_[0]);
          m_LineChartview->showlabel8->setText(item_text_list_[1]);
          m_LineChartview->showlabel9->setText(item_text_list_[2]);
          m_LineChartview->showlabel10->setText(item_text_list_[3]);
          m_LineChartview->showlabel11->setText(item_text_list_[4]);
          m_LineChartview->showlabel12->setText(item_text_list_[5]);
          m_LineChartview->showlabel13->setText(item_text_list_[6]);

          m_LineChartview->input_Series0->setBrush(point_color_list_[0]);
          m_LineChartview->input_Series0->setBorderColor(point_color_list_[0]);
          m_LineChartview->pe7.setColor(QPalette::Background,point_color_list_[0]);
          m_LineChartview->colorlabel7->setPalette(m_LineChartview->pe7);

          m_LineChartview->input_Series1->setBrush(point_color_list_[1]);
          m_LineChartview->input_Series1->setBorderColor(point_color_list_[1]);
          m_LineChartview->pe8.setColor(QPalette::Background,point_color_list_[1]);
          m_LineChartview->colorlabel8->setPalette(m_LineChartview->pe8);

          m_LineChartview->input_Series2->setBrush(point_color_list_[2]);
          m_LineChartview->input_Series2->setBorderColor(point_color_list_[2]);
          m_LineChartview->pe9.setColor(QPalette::Background,point_color_list_[2]);
          m_LineChartview->colorlabel9->setPalette(m_LineChartview->pe9);

          m_LineChartview->input_Series3->setBrush(point_color_list_[3]);
          m_LineChartview->input_Series3->setBorderColor(point_color_list_[3]);
          m_LineChartview->pe10.setColor(QPalette::Background,point_color_list_[3]);
          m_LineChartview->colorlabel10->setPalette(m_LineChartview->pe10);

          m_LineChartview->combine_Series0->setBrush(point_color_list_[4]);
          m_LineChartview->combine_Series0->setBorderColor(point_color_list_[4]);
          m_LineChartview->pe11.setColor(QPalette::Background,point_color_list_[4]);
          m_LineChartview->colorlabel11->setPalette(m_LineChartview->pe11);

          m_LineChartview->combine_Series1->setBrush(point_color_list_[5]);
          m_LineChartview->combine_Series1->setBorderColor(point_color_list_[5]);
          m_LineChartview->pe12.setColor(QPalette::Background,point_color_list_[5]);
          m_LineChartview->colorlabel12->setPalette(m_LineChartview->pe12);

          m_LineChartview->combine_Series2->setBrush(point_color_list_[6]);
          m_LineChartview->combine_Series2->setBorderColor(point_color_list_[6]);
          m_LineChartview->pe13.setColor(QPalette::Background,point_color_list_[6]);
          m_LineChartview->colorlabel13->setPalette(m_LineChartview->pe13);

          m_LineChartview->input_Series0->setMarkerSize(size_);
          m_LineChartview->input_Series1->setMarkerSize(size_);
          m_LineChartview->input_Series2->setMarkerSize(size_);
          m_LineChartview->input_Series3->setMarkerSize(size_);
          m_LineChartview->combine_Series0->setMarkerSize(size_);
          m_LineChartview->combine_Series1->setMarkerSize(size_);
          m_LineChartview->combine_Series2->setMarkerSize(size_);

          m_LineChartview->m_LineChart1->setBackgroundBrush(chartcolor_);

      });

      connect(setbackbtn2,&QPushButton::clicked,[=](){

          m_LineChartview->m_AxisX1->setTitleText(strText_x_axis1);
          x_name_->setText("Saturation");
          x_name_text_ = "Saturation";

          m_LineChartview->m_AxisX1->setRange(0,1);
          x_range1_->setText("0");
          x_range2_->setText("1");
          x_range1_text_ = "0";
          x_range2_text_ = "1";

          m_LineChartview->m_AxisY1->setTitleText(strText_y_axis1);
          y_name_->setText("Permeability");
          y_name_text_ = "Permeability";

          m_LineChartview->m_AxisY1->setRange(0,1);
          y_range1_->setText("0");
          y_range2_->setText("1");
          y_range1_text_ = "0";
          y_range2_text_ = "1";

          m_LineChartview->m_LineChart1->setTitle(strText1);
          title_->setText(Chartname1);
          title_text_ = Chartname1;

          m_LineChartview->input_Series0->setName("Original Data 1");
          m_LineChartview->input_Series1->setName("Original Data 2");
          m_LineChartview->input_Series2->setName("Original Data 3");
          m_LineChartview->input_Series3->setName("Original Data 4");
          m_LineChartview->combine_Series0->setName("Combined Data 1");
          m_LineChartview->combine_Series1->setName("Combined Data 2");
          m_LineChartview->combine_Series2->setName("Combined Data 3");

          m_LineChartview->showlabel7->setText("Original Data 1");
          m_LineChartview->showlabel8->setText("Original Data 2");
          m_LineChartview->showlabel9->setText("Original Data 3");
          m_LineChartview->showlabel10->setText("Original Data 4");
          m_LineChartview->showlabel11->setText("Combined Data 1");
          m_LineChartview->showlabel12->setText("Combined Data 2");
          m_LineChartview->showlabel13->setText("Combined Data 3");

          item_text_list_[0] = "Original Data 1";
          item_text_list_[1] = "Original Data 2";
          item_text_list_[2] = "Original Data 3";
          item_text_list_[3] = "Original Data 4";
          item_text_list_[4] = "Combined Data 1";
          item_text_list_[5] = "Combined Data 2";
          item_text_list_[6] = "Combined Data 3";

          legendBox_->setItemText(0,"Original Data 1");
          legendBox_->setItemText(1,"Original Data 2");
          legendBox_->setItemText(2,"Original Data 3");
          legendBox_->setItemText(3,"Original Data 4");
          legendBox_->setItemText(4,"Combined Data 1");
          legendBox_->setItemText(5,"Combined Data 2");
          legendBox_->setItemText(6,"Combined Data 3");

          m_LineChartview->input_Series0->setBrush(QColor(0,191,255));
          m_LineChartview->input_Series0->setBorderColor(QColor(0,191,255));
          point_color_list_[0] = QColor(0,191,255);
          m_LineChartview->pe7.setColor(QPalette::Background,point_color_list_[0]);
          m_LineChartview->colorlabel7->setPalette(m_LineChartview->pe7);

          m_LineChartview->input_Series1->setBrush(QColor(255,165,0));
          m_LineChartview->input_Series1->setBorderColor(QColor(255,165,0));
          point_color_list_[1] = QColor(255,165,0);
          m_LineChartview->pe8.setColor(QPalette::Background,point_color_list_[1]);
          m_LineChartview->colorlabel8->setPalette(m_LineChartview->pe8);


          m_LineChartview->input_Series2->setBrush(QColor(60,179,113));
          m_LineChartview->input_Series2->setBorderColor(QColor(60,179,113));
          point_color_list_[2] = QColor(60,179,113);
          m_LineChartview->pe9.setColor(QPalette::Background,point_color_list_[2]);
          m_LineChartview->colorlabel9->setPalette(m_LineChartview->pe9);


          m_LineChartview->input_Series3->setBrush(QColor(0,139,139));
          m_LineChartview->input_Series3->setBorderColor(QColor(0,139,139));
          point_color_list_[3] = QColor(0,139,139);
          m_LineChartview->pe10.setColor(QPalette::Background,point_color_list_[3]);
          m_LineChartview->colorlabel10->setPalette(m_LineChartview->pe10);


          m_LineChartview->combine_Series0->setBrush(QColor(255,20,147));
          m_LineChartview->combine_Series0->setBorderColor(QColor(255,20,147));
          point_color_list_[4] = QColor(255,20,147);
          m_LineChartview->pe11.setColor(QPalette::Background,point_color_list_[4]);
          m_LineChartview->colorlabel11->setPalette(m_LineChartview->pe11);


          m_LineChartview->combine_Series1->setBrush(QColor(123,104,238));
          m_LineChartview->combine_Series1->setBorderColor(QColor(123,104,238));
          point_color_list_[5] = QColor(123,104,238);
          m_LineChartview->pe12.setColor(QPalette::Background,point_color_list_[5]);
          m_LineChartview->colorlabel12->setPalette(m_LineChartview->pe12);


          m_LineChartview->combine_Series2->setBrush(QColor(139,0,0));
          m_LineChartview->combine_Series2->setBorderColor(QColor(139,0,0));
          point_color_list_[6] = QColor(139,0,0);
          m_LineChartview->pe13.setColor(QPalette::Background,point_color_list_[6]);
          m_LineChartview->colorlabel13->setPalette(m_LineChartview->pe13);

          size_ =8;
          m_LineChartview->input_Series0->setMarkerSize(size_);
          m_LineChartview->input_Series1->setMarkerSize(size_);
          m_LineChartview->input_Series2->setMarkerSize(size_);
          m_LineChartview->input_Series3->setMarkerSize(size_);
          m_LineChartview->combine_Series0->setMarkerSize(size_);
          m_LineChartview->combine_Series1->setMarkerSize(size_);
          m_LineChartview->combine_Series2->setMarkerSize(size_);

          chartcolor_ = Qt::white;
          m_LineChartview->m_LineChart1->setBackgroundBrush(Qt::white);

      });


      return FifthBox;
}

double theapp::Masuda_func(double Masuda_N_func , double Masuda_SH_func[] , double Masuda_kn_func[])
{
     int i = 0;
     double z = 0;
     for(;i<N;i++)
     {
        z += pow((pow((1 -  Masuda_SH_func[i]),Masuda_N_func) - Masuda_kn_func[i]),2);
     }
     return  z;
}

double theapp::Patchy_func(double Patchy_N_func , double Patchy_SH_func[] , double Patchy_kn_func[])
{
     int i = 0;
     double z = 0;
     for(;i<N;i++)
     {
        z += pow((pow((1 - Patchy_SH_func[i]),3)/pow((1 + 2 * Patchy_SH_func[i]),Patchy_N_func) - Patchy_kn_func[i]),2);
     }
     return  z;
}

double theapp::Hybrid_func(double Hybrid_alpha_func , double Hybrid_beta_func , double Hybrid_SH_func[] , double Hybrid_kn_func[])
{
     int i = 0;
     double z = 0;
     double GC_kn_func = 0;
     double PF_kn_func = 0;
     for(;i<N;i++)
     {
        GC_kn_func = pow((1 - Hybrid_SH_func[i]),2);
        PF_kn_func = (1 - pow(Hybrid_SH_func[i],2) + 2 * pow((1 - Hybrid_SH_func[i]),2)/qLn(Hybrid_SH_func[i]));
        z += pow((pow(GC_kn_func,(1/(1 + pow((Hybrid_SH_func[i]/Hybrid_alpha_func),Hybrid_beta_func)))) * pow(PF_kn_func,(1 - (1/(1 + pow((Hybrid_SH_func[i]/Hybrid_alpha_func),Hybrid_beta_func))))) - Hybrid_kn_func[i]),2);
     }
     return  z;
}
void theapp::fitting_calculate()
{

    a_fit3 = (x3y_sum*x2_sum*x2_sum*x5_sum - x6_sum*x2y_sum*x2_sum*x2_sum - 2*x3y_sum*x2_sum*x3_sum*x4_sum
              + x2y_sum*x2_sum*x3_sum*x5_sum + x6_sum*xy_sum*x2_sum*x3_sum + x2y_sum*x2_sum*x4_sum*x4_sum
              - xy_sum*x2_sum*x4_sum*x5_sum + x6_sum*y_sum*x2_sum*x4_sum - y_sum*x2_sum*x5_sum*x5_sum
              + x3y_sum*x3_sum*x3_sum*x3_sum - x2y_sum*x3_sum*x3_sum*x4_sum - xy_sum*x3_sum*x3_sum*x5_sum - x6_sum*y_sum*x3_sum*x3_sum
              + xy_sum*x3_sum*x4_sum*x4_sum + 2*y_sum*x3_sum*x4_sum*x5_sum - x3y_sum*x_sum*x3_sum*x5_sum
              + x6_sum*x2y_sum*x_sum*x3_sum - y_sum*x4_sum*x4_sum*x4_sum + x3y_sum*x_sum*x4_sum*x4_sum - x2y_sum*x_sum*x4_sum*x5_sum
              - x6_sum*x_sum*xy_sum*x4_sum + x_sum*xy_sum*x5_sum*x5_sum)/(- x6_sum*x2_sum*x2_sum*x2_sum
              + 2*x2_sum*x2_sum*x3_sum*x5_sum + x2_sum*x2_sum*x4_sum*x4_sum - 3*x2_sum*x3_sum*x3_sum*x4_sum
              + 2*x6_sum*x2_sum*x3_sum*x_sum - 2*x2_sum*x4_sum*x5_sum*x_sum + N*x6_sum*x2_sum*x4_sum - N*x2_sum*x5_sum*x5_sum
              + x3_sum*x3_sum*x3_sum*x3_sum - 2*x3_sum*x3_sum*x5_sum*x_sum - N*x6_sum*x3_sum*x3_sum + 2*x3_sum*x4_sum*x4_sum*x_sum
              + 2*N*x3_sum*x4_sum*x5_sum - N*x4_sum*x4_sum*x4_sum - x6_sum*x4_sum*x_sum*x_sum + x5_sum*x5_sum*x_sum*x_sum);

    b_fit3 = -(x2_sum*x3_sum*x3_sum*x3y_sum - x3_sum*x3_sum*x3_sum*x2y_sum - x2_sum*x2_sum*x4_sum*x3y_sum + x3_sum*x3_sum*x4_sum*xy_sum
               + x2_sum*x2_sum*x6_sum*xy_sum - x3_sum*x4_sum*x4_sum*y_sum + x3_sum*x3_sum*x5_sum*y_sum - x5_sum*x5_sum*x_sum*y_sum
               + N*x4_sum*x4_sum*x3y_sum + N*x5_sum*x5_sum*xy_sum - N*x3_sum*x5_sum*x3y_sum + N*x3_sum*x6_sum*x2y_sum
               - N*x4_sum*x5_sum*x2y_sum - N*x4_sum*x6_sum*xy_sum + x2_sum*x3_sum*x4_sum*x2y_sum + x2_sum*x5_sum*x3y_sum*x_sum
               - x2_sum*x6_sum*x2y_sum*x_sum - x3_sum*x4_sum*x3y_sum*x_sum + x3_sum*x5_sum*x2y_sum*x_sum - 2*x2_sum*x3_sum*x5_sum*xy_sum
               - x2_sum*x3_sum*x6_sum*y_sum + x2_sum*x4_sum*x5_sum*y_sum + x4_sum*x6_sum*x_sum*y_sum)/(- x6_sum*x2_sum*x2_sum*x2_sum
               + 2*x2_sum*x2_sum*x3_sum*x5_sum + x2_sum*x2_sum*x4_sum*x4_sum - 3*x2_sum*x3_sum*x3_sum*x4_sum
               + 2*x6_sum*x2_sum*x3_sum*x_sum - 2*x2_sum*x4_sum*x5_sum*x_sum + N*x6_sum*x2_sum*x4_sum - N*x2_sum*x5_sum*x5_sum
               + x3_sum*x3_sum*x3_sum*x3_sum - 2*x3_sum*x3_sum*x5_sum*x_sum - N*x6_sum*x3_sum*x3_sum + 2*x3_sum*x4_sum*x4_sum*x_sum
               + 2*N*x3_sum*x4_sum*x5_sum - N*x4_sum*x4_sum*x4_sum - x6_sum*x4_sum*x_sum*x_sum + x5_sum*x5_sum*x_sum*x_sum);

    c_fit3 = -(x2_sum*x3_sum*x3_sum*x2y_sum - x3_sum*x3_sum*x3_sum*xy_sum - x2_sum*x2_sum*x3_sum*x3y_sum + x3_sum*x3_sum*x3y_sum*x_sum - x5_sum*x3y_sum*x_sum*x_sum
               + x6_sum*x2y_sum*x_sum*x_sum - x2_sum*x4_sum*x4_sum*y_sum + x3_sum*x3_sum*x4_sum*y_sum + x2_sum*x2_sum*x6_sum*y_sum + N*x4_sum*x4_sum*x2y_sum
               + N*x2_sum*x5_sum*x3y_sum - N*x2_sum*x6_sum*x2y_sum - N*x3_sum*x4_sum*x3y_sum + N*x3_sum*x6_sum*xy_sum - N*x4_sum*x5_sum*xy_sum
               + x2_sum*x4_sum*x3y_sum*x_sum - 2*x3_sum*x4_sum*x2y_sum*x_sum + x2_sum*x3_sum*x4_sum*xy_sum - x2_sum*x6_sum*x_sum*xy_sum
               + x3_sum*x5_sum*x_sum*xy_sum - x2_sum*x3_sum*x5_sum*y_sum - x3_sum*x6_sum*x_sum*y_sum + x4_sum*x5_sum*x_sum*y_sum)/(- x6_sum*x2_sum*x2_sum*x2_sum
               + 2*x2_sum*x2_sum*x3_sum*x5_sum + x2_sum*x2_sum*x4_sum*x4_sum - 3*x2_sum*x3_sum*x3_sum*x4_sum + 2*x6_sum*x2_sum*x3_sum*x_sum
               - 2*x2_sum*x4_sum*x5_sum*x_sum + N*x6_sum*x2_sum*x4_sum - N*x2_sum*x5_sum*x5_sum + x3_sum*x3_sum*x3_sum*x3_sum
               - 2*x3_sum*x3_sum*x5_sum*x_sum - N*x6_sum*x3_sum*x3_sum + 2*x3_sum*x4_sum*x4_sum*x_sum + 2*N*x3_sum*x4_sum*x5_sum
               - N*x4_sum*x4_sum*x4_sum - x6_sum*x4_sum*x_sum*x_sum + x5_sum*x5_sum*x_sum*x_sum);

    d_fit3 = -(x3y_sum*x2_sum*x2_sum*x2_sum - x2y_sum*x2_sum*x2_sum*x3_sum - xy_sum*x2_sum*x2_sum*x4_sum - x5_sum*y_sum*x2_sum*x2_sum + xy_sum*x2_sum*x3_sum*x3_sum
               + 2*y_sum*x2_sum*x3_sum*x4_sum - 2*x3y_sum*x2_sum*x3_sum*x_sum + x2y_sum*x2_sum*x4_sum*x_sum - N*x3y_sum*x2_sum*x4_sum
               + x5_sum*xy_sum*x2_sum*x_sum + N*x5_sum*x2y_sum*x2_sum - y_sum*x3_sum*x3_sum*x3_sum + x2y_sum*x3_sum*x3_sum*x_sum + N*x3y_sum*x3_sum*x3_sum
               - xy_sum*x3_sum*x4_sum*x_sum - N*x2y_sum*x3_sum*x4_sum + x5_sum*y_sum*x3_sum*x_sum - N*x5_sum*xy_sum*x3_sum
               - y_sum*x4_sum*x4_sum*x_sum + N*xy_sum*x4_sum*x4_sum + x3y_sum*x4_sum*x_sum*x_sum - x5_sum*x2y_sum*x_sum*x_sum)/(- x6_sum*x2_sum*x2_sum*x2_sum
               + 2*x2_sum*x2_sum*x3_sum*x5_sum + x2_sum*x2_sum*x4_sum*x4_sum - 3*x2_sum*x3_sum*x3_sum*x4_sum + 2*x6_sum*x2_sum*x3_sum*x_sum
               - 2*x2_sum*x4_sum*x5_sum*x_sum + N*x6_sum*x2_sum*x4_sum - N*x2_sum*x5_sum*x5_sum + x3_sum*x3_sum*x3_sum*x3_sum
               - 2*x3_sum*x3_sum*x5_sum*x_sum - N*x6_sum*x3_sum*x3_sum + 2*x3_sum*x4_sum*x4_sum*x_sum + 2*N*x3_sum*x4_sum*x5_sum
               - N*x4_sum*x4_sum*x4_sum - x6_sum*x4_sum*x_sum*x_sum + x5_sum*x5_sum*x_sum*x_sum);


    for(int i=0;i<60;i++)
    {
        if(m_LineChartview->input_SH[i] == 0 &&m_LineChartview->input_kn[i] == 0)
        {break;}
        m_LineChartview->fitting3_kn[i] = a_fit3 + b_fit3 * m_LineChartview->fitting3_SH[i] + c_fit3 * m_LineChartview->fitting3_SH[i] * m_LineChartview->fitting3_SH[i]+ d_fit3 * m_LineChartview->fitting3_SH[i] * m_LineChartview->fitting3_SH[i] * m_LineChartview->fitting3_SH[i];

    }
}
theapp::~theapp()
{
    delete ui;
}

