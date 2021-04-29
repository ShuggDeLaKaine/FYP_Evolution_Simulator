function FIS_5
%first clear the screen.
%clc;
%var to hold excel file.
data1 = ('Data.xlsx');
%read data from xls file and store in testData.
inputData = xlsread(data1);

%{
FIS::5.1 - Final Check.
Input: Polluntant(Input::FIS::1.1), Survivability(Output::FIS::4.1)
Output: FINAL::Final Score.
%}
%new Fuzzy Inference System called 'Final Check'.
fis5 = newfis('Final Check', 'DefuzzificationMethod', 'mom', 'AndMethod', 'min', ...
                             'ImplicationMethod', 'min', 'AggregationMethod', 'max')

%declare 'Pollutant Present' INPUT variable.
fis5 = addvar(fis5, 'input', 'Pollutant Present (%)', [0 100]);
%declare MFs for Polluate Present input.
fis5 = addmf(fis5, 'input', 1, 'No Pollution', 'zmf', [0 3]);
fis5 = addmf(fis5, 'input', 1, 'Low Pollution', 'gbellmf', [17.5 3 15]);
fis5 = addmf(fis5, 'input', 1, 'Moderate Pollution', 'gaussmf', [15 50]);
fis5 = addmf(fis5, 'input', 1, 'High Pollution', 'gbellmf', [17.5 3 85]);
fis5 = addmf(fis5, 'input', 1, 'Complete Pollution', 'smf', [95 100]);
%declare the INPUT variable 'Survivability'.
fis5 = addvar(fis5, 'input', 'Survive Chance', [-100 100]);
%declare MFs for  input variable.
fis5 = addmf(fis5, 'input', 2, 'Impossible', 'zmf', [-98 -95]);
fis5 = addmf(fis5, 'input', 2, 'Very Low', 'gaussmf', [25 -80]);
fis5 = addmf(fis5, 'input', 2, 'Low', 'gaussmf', [25 -40]);
fis5 = addmf(fis5, 'input', 2, 'Possible', 'gaussmf', [25 0 ]);
fis5 = addmf(fis5, 'input', 2, 'High', 'gaussmf', [25 40]);
fis5 = addmf(fis5, 'input', 2, 'Very High', 'gaussmf', [25 80]);
fis5 = addmf(fis5, 'input', 2, 'Guaranteed', 'smf', [95 98]);
%declare the OUTPUT variable 'Final Score'.
fis5 = addvar(fis5, 'output', 'Final Score', [-100 100]);
%declare MFs for  output variable.
fis5 = addmf(fis5, 'output', 1, 'Impossible', 'zmf', [-98 -95]);
fis5 = addmf(fis5, 'output', 1, 'Very Low', 'gaussmf', [25 -80]);
fis5 = addmf(fis5, 'output', 1, 'Low', 'gaussmf', [25 -40]);
fis5 = addmf(fis5, 'output', 1, 'Possible', 'gaussmf', [25 0 ]);
fis5 = addmf(fis5, 'output', 1, 'High', 'gaussmf', [25 40]);
fis5 = addmf(fis5, 'output', 1, 'Very High', 'gaussmf', [25 80]);
fis5 = addmf(fis5, 'output', 1, 'Guaranteed', 'smf', [95 98]);

%RULES(25) In:Pollution(5), In:Survivability(6), Out:Final Score(7), Weight=1,(AND) //  5 x 6 = 30.
rule1  = [5 1 1 1 2];     %[In:Complete Pollution, In:Impossible, Out:Impossible, (1), OR]
rule2  = [1 2 2 1 1];     %[In:No Pollution, In:Very Low, Out:Very Low, (1), AND]
rule3  = [1 3 3 1 1];     %[In:No Pollution, In:Low, Out:Low, (1), AND]
rule4  = [1 4 4 1 1];     %[In:No Pollution, In:Possible, Out:Possible, (1), AND]
rule5  = [1 5 5 1 1];     %[In:No Pollution, In:High, Out:High, (1), AND]
rule6  = [1 6 6 1 1];     %[In:No Pollution, In:Very High, Out:Very High, (1), AND]
rule7  = [1 7 7 1 1];     %[In:No Pollution, In:Guaranteed, Out:Guaranteed, (1), AND]
rule8  = [2 2 1 1 1];     %[In:Low Pollution, In:Very Low, Out:Impossible, (1), AND]
rule9  = [2 3 2 1 1];     %[In:Low Pollution, In:Low, Out:Very Low, (1), AND]
rule10 = [2 4 3 1 1];     %[In:Low Pollution, In:Possible, Out:Low, (1), AND]
rule11 = [2 5 4 1 1];     %[In:Low Pollution, In:High, Out:Possible, (1), AND]
rule12 = [2 6 5 1 1];     %[In:Low Pollution, In:Very High, Out:High, (1), AND]
rule13 = [2 7 6 1 1];     %[In:Low Pollution, In:Guaranteed, Out:Very High, (1), AND]
rule14 = [3 2 1 1 1];     %[In:Moderate Pollution, In:Very Low, Out:Impossible, (1), AND]
rule15 = [3 3 1 1 1];     %[In:Moderate Pollution, In:Low, Out:Impossible, (1), AND]
rule16 = [3 4 2 1 1];     %[In:Moderate Pollution, In:Possible, Out:Very Low, (1), AND]
rule17 = [3 5 3 1 1];     %[In:Moderate Pollution, In:High, Out:Low, (1), AND]
rule18 = [3 6 4 1 1];     %[In:Moderate Pollution, In:Very High, Out:Possible, (1), AND]
rule19 = [3 7 5 1 1];     %[In:Moderate Pollution, In:Guaranteed, Out:High, (1), AND]
rule20 = [4 2 1 1 1];     %[In:High Pollution, In:Very Low, Out:Impossible, (1), AND]
rule21 = [4 3 1 1 1];     %[In:High Pollution, In:Low, Out:Impossible, (1), AND]
rule22 = [4 4 1 1 1];     %[In:High Pollution, In:Possible, Out:Impossible, (1), AND]
rule23 = [4 5 2 1 1];     %[In:High Pollution, In:High, Out:Very Low, (1), AND]
rule24 = [4 6 3 1 1];     %[In:High Pollution, In:Very High, Out:Low, (1), AND]
rule25 = [4 7 4 1 1];     %[In:High Pollution, In:Guaranteed, Out:Possible, (1), AND]

%rule list, placing the individual ARRAYS into a MATRIX
firstSurviveCheckRuleList = [ rule1; rule2; rule3; rule4; rule5; rule6; rule7; rule8; rule9; rule10; 
    rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19; rule20; rule21; rule22; 
    rule23; rule24; rule25 ];

%addrule passes the rulesList into out FIS (a).
fis5 = addRule(fis5, firstSurviveCheckRuleList);
%Display the rules of the FIS.
showrule(fis5)

%DATA OUTPUT - loop to run through the data, then output & write results.
for i=1:size(inputData, 1)
    %var output to hold result of EVALFIS for the first 2 columns of INPUT data at row i in the excel document.
    output = evalfis([inputData(i, 2), inputData(i, 9)], fis5);
    %prints to console window, shows input values being fed into system.
    fprintf('%d) In(1): %.2f, In(2) %.2f => Out: %.2f \n\n', i, inputData(i, 2), inputData(i, 9), output);
    %write to result of FIS1 to InputData column E.
    xlswrite('InputData.xlsx', output, 1, sprintf('J%d', i + 1));
end

end