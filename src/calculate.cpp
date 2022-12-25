#include "calculate.h"
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QButtonGroup>
#include <QMessageBox>
#include <QDebug>
Calculate::Calculate(QWidget *parent) : QWidget(parent)
{

    QFont titlefont("Times New Roman");
    setWindowTitle("Calculator");
    setFont(titlefont);
    setGeometry(200,100,440,280);
    setFixedSize(440,280);

    QPushButton *startbtn = new QPushButton(this);

    startbtn->setText("Calculate");
    startbtn->setGeometry(50,180,110,50);
    startbtn->setStyleSheet(btnstyle);

    QLabel *SH_label = new QLabel("Input Saturation",this);
    SH_label->setGeometry(15,0,200,40);
    SH_label->setStyleSheet(label_str);

    QLabel *kn_label = new QLabel("Output Permeability",this);
    kn_label->setGeometry(15,80,200,40);
    kn_label->setStyleSheet(label_str);


    QLineEdit *input_SH = new QLineEdit(this);
    input_SH->setText("");
    input_SH->setGeometry(5,40,200,40);
    input_SH->setReadOnly(0);
    input_SH->setStyleSheet(lineedit_str);

    QLineEdit *output_kn = new QLineEdit(this);
    output_kn->setText("");
    output_kn->setGeometry(5,120,200,40);
    output_kn->setReadOnly(0);
    output_kn->setStyleSheet(lineedit_str);

    spinbox = new QSpinBox(this);
    QLabel *spinlabel = new QLabel(this);
    spinlabel->setText("Decimal places:");
    spinlabel->setStyleSheet(label_str);
    spinlabel->setGeometry(220,5,150,30);
    spinbox->setGeometry(378,5,50,30);
    spinbox->setRange(0,6);
    spinbox->setValue(2);
    spinbox->setWrapping(true);

    connect(spinbox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](){
         if(spinbox->value() == 0)
         {output_kn->setText(QString::number(kn,'f',0));}
         if(spinbox->value() == 1)
         {output_kn->setText(QString::number(kn,'f',1));}
         if(spinbox->value() == 2)
         {output_kn->setText(QString::number(kn,'f',2));}
         if(spinbox->value() == 3)
         {output_kn->setText(QString::number(kn,'f',3));}
         if(spinbox->value() == 4)
         {output_kn->setText(QString::number(kn,'f',4));}
         if(spinbox->value() == 5)
         {output_kn->setText(QString::number(kn,'f',5));}
         if(spinbox->value() == 6)
         {output_kn->setText(QString::number(kn,'f',6));}

    });

    createFirstGroup()->setParent(this);



    connect(startbtn,&QPushButton::clicked,[=](){


        if(input_SH->text()=="" || input_SH->text()==" "){
          QMessageBox::information(this,"Warning","Input Data is not found, Calculator can not work");
        }
        else if(model == 0){
          QMessageBox::information(this,"Warning","Warning Model choice is empty, Calculator can not work");
        }

        else{
        calculate(input_SH->text());
        QString str1 = QString::number(kn,'f',2);
        output_kn->setText(str1);}



    });
}

QGroupBox *Calculate::createFirstGroup()
{
      QGroupBox *groupBox = new QGroupBox(tr("Models"));
      group = new QButtonGroup(groupBox);
      groupBox->setGeometry(235,40,160,220);
      groupBox->setStyleSheet(groupstyle);
      modelbox1 = new QCheckBox(tr("Masuda"),groupBox);
      modelbox2 = new QCheckBox(tr("Patchy"),groupBox);
      modelbox3 = new QCheckBox(tr("G-C"),groupBox);
      modelbox4 = new QCheckBox(tr("P-F"),groupBox);
      modelbox5 = new QCheckBox(tr("Hybrid"),groupBox);

      modelbox1->setGeometry(10,30,150,30);
      modelbox2->setGeometry(10,60,150,30);
      modelbox3->setGeometry(10,90,150,30);
      modelbox4->setGeometry(10,120,150,30);
      modelbox5->setGeometry(10,150,150,30);

      modelbox1->setStyleSheet(checkboxstyle);
      modelbox2->setStyleSheet(checkboxstyle);
      modelbox3->setStyleSheet(checkboxstyle);
      modelbox4->setStyleSheet(checkboxstyle);
      modelbox5->setStyleSheet(checkboxstyle);

      modelbox1->setCheckState(Qt::Unchecked);
      modelbox2->setCheckState(Qt::Unchecked);
      modelbox3->setCheckState(Qt::Unchecked);
      modelbox4->setCheckState(Qt::Unchecked);
      modelbox5->setCheckState(Qt::Unchecked);

      group->addButton(modelbox1);
      group->addButton(modelbox2);
      group->addButton(modelbox3);
      group->addButton(modelbox4);
      group->addButton(modelbox5);

      connect(group, static_cast<void(QButtonGroup::*)(QAbstractButton *, bool)>(&QButtonGroup::buttonToggled),
            [=](){

          if(modelbox1->checkState() == Qt::Checked)
          {model = 1;}
          if(modelbox2->checkState() == Qt::Checked)
          {model = 2;}
          if(modelbox3->checkState() == Qt::Checked)
          {model = 3;}
          if(modelbox4->checkState() == Qt::Checked)
          {model = 4;}
          if(modelbox5->checkState() == Qt::Checked)
          {model = 5;}

          if(modelbox1->checkState()==0&&modelbox2->checkState()==0&&modelbox3->checkState()==0&&modelbox4->checkState()==0
             &&modelbox5->checkState()==0)
          {model = 0;}

      });

      return groupBox;
}


void Calculate::calculate(QString str)
{
   SH=str.toDouble();
    if(model == 1)
   {
      Masuda_SH = SH;
      Masuda_kn = pow((1 - Masuda_SH),Masuda_N);
      kn = Masuda_kn;
   }
    if(model == 2)
   {
      Patchy_SH = SH;
      Patchy_kr = pow((1 - Patchy_SH),3)/pow((1 + 2 * Patchy_SH),Patchy_N);
      kn = Patchy_kr;
   }
    if(model == 3)
   {
      GC_SH = SH;
      GC_kn = pow((1 - GC_SH),2);
      kn = GC_kn;
   }
    if(model == 4)
   {
      PF_SH = SH;
      PF_kn = (1 - pow(PF_SH,2) + 2 * pow((1 - PF_SH),2)/log(PF_SH));
      kn = PF_kn;
   }
    if(model == 5)
   {
      Hybrid_SH = SH;
      GC_kn = pow((1 - Hybrid_SH),2);
      PF_kn = (1 - pow(Hybrid_SH,2) + 2 * pow((1 - Hybrid_SH),2)/log(Hybrid_SH));
      Hybrid_kn = pow(GC_kn,(1/(1 + pow((Hybrid_SH/Hybrid_alpha),Hybrid_Beta)))) * pow(PF_kn,(1 - (1/(1 + pow((Hybrid_SH/Hybrid_alpha),Hybrid_Beta)))));
      kn = Hybrid_kn;
   }

}
