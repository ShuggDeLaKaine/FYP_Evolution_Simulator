function FIS_2
%first clear the screen.
%clc;
%var to hold excel file.
data1 = ('Data.xlsx');
%read data from xls file and store in testData.
inputData = xlsread(data1);

%{
FIS::2.1 - Heat Check.
Input: Light(Output::FIS::1.1), Alternate Heat Source.
Output: Heat.
%}
%new Fuzzy Inference System called 'Heat Level Check'.
fis2 = newfis('Heat Level Check', 'DefuzzificationMethod', 'centroid','AndMethod', 'prod', ... 
                                        'ImplicationMethod', 'prod', 'AggregationMethod', 'max')

%declare the 'Light Level' INPUT variable.
fis2 = addvar(fis2, 'input', 'Light Level (%)', [0 100]);
%declare MFs for Light input.
fis2 = addmf(fis2, 'input', 1, 'No Light', 'trapmf', [0 0 0 1]);
fis2 = addmf(fis2, 'input', 1, 'Low Light', 'pimf', [0 0.5 30 55]);
fis2 = addmf(fis2, 'input', 1, 'Moderate Light', 'gaussmf', [15 55]);
fis2 = addmf(fis2, 'input', 1, 'High Light', 'pimf', [60 85 99 100]);
fis2 = addmf(fis2, 'input', 1, 'Complete Light', 'smf', [98 100]);
%declare 'Alternate Heat Source' INPUT variable.
fis2 = addvar(fis2, 'input', 'Alternate Heat Source (c)', [-5 30]);
%declare MFs for Alternate Heat Source input.
fis2 = addmf(fis2, 'input', 2, 'None', 'trapmf', [-1.0 -0.5 0.5 1.0]);
fis2 = addmf(fis2, 'input', 2, 'Cold Current', 'gbellmf', [4.5 12 -5]);
fis2 = addmf(fis2, 'input', 2, 'Warm Current', 'pimf', [0 1 10 20]); 
fis2 = addmf(fis2, 'input', 2, 'Thermal Vents', 'smf', [10 20]);
%declare the OUTPUT variable Heat Level Check.
fis2 = addvar(fis2, 'output', 'Heat Level (c)', [-5 50]);
%declare MFs for Heat Levels output variable.
fis2 = addmf(fis2, 'output', 1, 'Freezing', 'trapmf', [-5 -5 0 0]); 
fis2 = addmf(fis2, 'output', 1, 'Cold', 'trapmf', [0 0.5 2 3]); 
fis2 = addmf(fis2, 'output', 1, 'Cool', 'pimf', [1 3 6 11]);
fis2 = addmf(fis2, 'output', 1, 'Temperate', 'gbellmf', [6.5 4 13]);
fis2 = addmf(fis2, 'output', 1, 'Warm', 'gbellmf', [7 4 24]);
fis2 = addmf(fis2, 'output', 1, 'Hot', 'gbellmf', [5 4 34]);
fis2 = addmf(fis2, 'output', 1, 'Very Hot', 'smf', [35 40]);   

%RULES(20) In:LIGHT(5), In:ALTERNATE_HEAT(4), Out:HEAT(7), Weight=1, (AND) // 5 x 4 = 20 rules max 
rule1  = [1 1 2 1 1];       %[In:No Light, In:None, Out:Cold, (1), AND]
rule2  = [1 2 2 1 1];       %[In:No Light, In:Cold Current, Out:Cold, (1), AND]
rule3  = [1 3 3 1 1];       %[In:No Light, In:Warm Current, Out:Cool, (1), AND]
rule4  = [1 4 5 1 1];       %[In:No Light, In:Thermal Vents, Out:Warm, (1), AND]
rule5  = [2 1 2 1 1];       %[In:Low Light, In:None, Out:Cold, (1), AND]
rule6  = [2 2 2 1 1];       %[In:Low Light, In:Cold Current, Out:Cold, (1), AND]
rule7  = [2 3 3 1 1];       %[In:Low Light, In:Warm Current, Out:Cool, (1), AND]
rule8  = [2 4 6 1 1];       %[In:Low Light, In:Thermal Vents, Out:Hot, (1), AND]
rule9  = [3 1 3 1 1];       %[In:Moderate Light, In:None, Out:Cool, (1), AND]
rule10 = [3 2 2 1 1];       %[In:Moderate Light, In:Cold Current, Out:Cold, (1), AND]
rule11 = [3 3 4 1 1];       %[In:Moderate Light, In:Warm Current, Out:Temperate, (1), AND]
rule12 = [3 4 6 1 1];       %[In:Moderate Light, In:Thermal Vents, Out:Hot, (1), AND]
rule13 = [4 1 4 1 1];       %[In:High Light, In:None, Out:Temperate, (1), AND]
rule14 = [4 2 4 1 1];       %[In:High Light, In:Cold Current, Out:Temperate, (1), AND]
rule15 = [4 3 5 1 1];       %[In:High Light, In:Warm Current, Out:Warm, (1), AND]
rule16 = [4 4 7 1 1];       %[In:High Light, In:Thermal Vents, Out:Very Hot, (1), AND]
rule17 = [5 1 5 1 1];       %[In:Complete Light, In:None, Out:Warm, (1), AND]
rule18 = [5 2 4 1 1];       %[In:Complete Light, In:Cold Current, Out:Temperate, (1), AND]
rule19 = [5 3 6 1 1];       %[In:Complete Light, In:Warm Current, Out:Hot, (1), AND]
rule20 = [5 4 7 1 1];       %[In:Complete Light, In:Thermal Vents, Out:Very Hot, (1), AND]

%rule list, placing the individual ARRAYS into a MATRIX
heatLevelRuleList = [ rule1; rule2; rule3; rule4; rule5; rule6; rule7; rule8; rule9; rule10; 
    rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19; rule20 ];

%addrule passes the rulesList into out FIS (a).
fis2 = addRule(fis2, heatLevelRuleList);
%Display the rules of the FIS.
showrule(fis2)

%DATA OUTPUT - loop to run through the data, then output & write results.
for i=1:size(inputData, 1)
    %var output to hold result of EVALFIS for the first 2 columns of INPUT data at row i in the excel document.
    output = evalfis([inputData(i, 5), inputData(i, 3)], fis2);
    %prints to console window, shows input values being fed into system.
    fprintf('%d) In(1): %.2f, In(2) %.2f => Out: %.2f \n\n', i, inputData(i, 5), inputData(i, 3), output);
    %write to result of FIS1 to InputData column E.
    xlswrite('InputData.xlsx', output, 1, sprintf('F%d', i + 1));
end

end