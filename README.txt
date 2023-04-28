Name of the software/program: 
ALPHA MODEL ver1.03
Name of the project: 
Newbee12.pro

Authors:  
Hao Weng*a, Zhengyang Liu*b, Dayong Wang*a
*a Key Laboratory of Ocean Energy Utilization and Energy Conservation of Ministry of Education, School of Energy and Power Engineering, Dalian University of Technology, Dalian 116023, P. R. China
*b Department of Mechanical Engineering, National University of Singapore, 9 Engineering Drive 1, 117575 Singapore, Singapore
  
Corresponding author. 
Dayong Wang
School of Energy and Power Engineering 
Dalian University of Technology 
2 Linggong Road 
Dalian 116023 
P. R. China 

Contact Email: wangdy@dlut.edu.cn

----------------------------------------------------------------------------------------------------------------------------
The source codes are included in the src/ folder. They need to be run in the Window OS, Debug mode in Qt Creator ver 5.9.9, C++11 and MinGW_32bit kit pack. Click the "Newbee12.pro" to run the code. Because the MinGW_32bit kit is an old pack and the Qt version is old, you may fail to run the source codes for many reasons. 
----------------------------------------------------------------------------------------------------------------------------
Considering this, we packaged the project into an executable software in the ALPHA MODEL/ folder. You can download this folder, open and click the "ALPHA MODEL.exe" to run this program without Qt creator. We highly recommend you to run the program in this way.
----------------------------------------------------------------------------------------------------------------------------
More guidelines and .txt files are included in the docs/ folder.
The helpfile.txt contains instruction guide that provides information on how to use the functions in the program.
The test data is excel_example.xlsx. You can use this file as input data.
----------------------------------------------------------------------------------------------------------------------------
Warning:
1. The reference exponent range of the Tokyo model is 0 to 20. If the inputted exponent value is beyond the reference range, the "Factor Change" function in the "Model Fitting and Comparison" module may lead to deviations and trigger the warning window.
