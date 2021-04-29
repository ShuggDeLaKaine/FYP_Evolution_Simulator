function FIS_4
%first clear the screen.
%clc;
%var to hold excel file.
data1 = ('Data.xlsx');
%read data from xls file and store in testData.
inputData = xlsread(data1);

%{
FIS::4.1 - Survivability Check.
Input: Polluntant(Input::FIS::1.1), Energy Available(Output::FIS::3.1), Oxygen(Output::FIS::3.2)
Output: FINAL::Survivability.
%}
%new Fuzzy Inference System called 'Survivability Check'.
    fis4 = newfis('Survivability Check', 'DefuzzificationMethod', 'lom', 'AndMethod', 'prod', ...
                                        'ImplicationMethod', 'prod', 'AggregationMethod', 'max');

%declare the INPUT variable 'Energy Available'.
fis4 = addvar(fis4, 'input', 'Energy Available (J)', [0 1000]);
%declare MFs for Energy output variable.
fis4 = addmf(fis4, 'input', 1, 'Barren', 'zmf', [10 100]);
fis4 = addmf(fis4, 'input', 1, 'Sparse', 'gbellmf', [135 4 200]);
fis4 = addmf(fis4, 'input', 1, 'Moderate', 'gbellmf', [150 4 480]);
fis4 = addmf(fis4, 'input', 1, 'Abundant', 'gbellmf', [145 4 760]);
fis4 = addmf(fis4, 'input', 1, 'Eden', 'smf', [850 950]);
%declare the OUTPUT variable 'Oxygenation Rate'.
fis4 = addvar(fis4, 'input', 'Oxygenation Rate (%)', [0 100]);
%declare MFs for Oxygen output variable.
fis4 = addmf(fis4, 'input', 2, 'Death Zone', 'zmf', [0.25 1]);
fis4 = addmf(fis4, 'input', 2, 'Very Low', 'gbellmf', [12 2.5 10]);
fis4 = addmf(fis4, 'input', 2, 'Low', 'gbellmf', [14 3 30]);
fis4 = addmf(fis4, 'input', 2, 'Moderate', 'gbellmf', [14 3 55]);
fis4 = addmf(fis4, 'input', 2, 'High', 'gbellmf', [14 3 78]);
fis4 = addmf(fis4, 'input', 2, 'Very High', 'smf', [83 92]);
%declare the OUTPUT variable 'Survivability'.
fis4 = addvar(fis4, 'output', 'Survive Chance', [-100 100]);
%declare MFs for  output variable.
fis4 = addmf(fis4, 'output', 1, 'Impossible', 'zmf', [-98 -95]);
fis4 = addmf(fis4, 'output', 1, 'Very Low', 'gaussmf', [25 -80]);
fis4 = addmf(fis4, 'output', 1, 'Low', 'gaussmf', [25 -40]);
fis4 = addmf(fis4, 'output', 1, 'Possible', 'gaussmf', [25 0 ]);
fis4 = addmf(fis4, 'output', 1, 'High', 'gaussmf', [25 40]);
fis4 = addmf(fis4, 'output', 1, 'Very High', 'gaussmf', [25 80]);
fis4 = addmf(fis4, 'output', 1, 'Guaranteed', 'smf', [95 98]);

%RULES(26)rules76-101: In:ENERGY(5), In:Oxygen(6), Out:Survivability(7), Weight=1,(AND) //  5 x 6 = 30.
rule1  = [0 1 1 1 1];     %[In:Any, In:Death Zone, Out:Impossible, (1), AND]
rule2  = [1 2 2 1 1];     %[In:Barren, In:Very Low, Out:Very Low, (1), AND]
rule3  = [1 3 2 1 1];     %[In:Barren, In:Low, Out:Very Low, (1), AND]
rule4  = [1 4 2 1 1];     %[In:Barren, In:Moderate, Out:Very Low, (1), AND]
rule5  = [1 5 2 1 1];     %[In:Barren, In:High, Out:Very Low, (1), AND]
rule6  = [1 6 2 1 1];     %[In:Barren, In:Very High, Out:Very Low, (1), AND]
rule7  = [2 2 2 1 1];     %[In:Sparse, In:Very Low, Out:Very Low, (1), AND]
rule8  = [2 3 3 1 1];     %[In:Sparse, In:Low, Out:Low, (1), AND]
rule9  = [2 4 3 1 1];     %[In:Sparse, In:Moderate, Out:Low, (1), AND]
rule10 = [2 5 4 1 1];     %[In:Sparse, In:High, Out:Possible, (1), AND]
rule11 = [2 6 4 1 1];     %[In:Sparse, In:Very High, Out:Possible, (1), AND]
rule12 = [3 2 3 1 1];     %[In:Moderate, In:Very Low, Out:Low, (1), AND]
rule13 = [3 3 4 1 1];     %[In:Moderate, In:Low, Out:Possible, (1), AND]
rule14 = [3 4 4 1 1];     %[In:Moderate, In:Moderate, Out:Possible, (1), AND]
rule15 = [3 5 5 1 1];     %[In:Moderate, In:High, Out:High, (1), AND]
rule16 = [3 6 5 1 1];     %[In:Moderate, In:Very High, Out:High, (1), AND]
rule17 = [4 2 4 1 1];     %[In:Abundant, In:Very Low, Out:Possible, (1), AND]
rule18 = [4 3 5 1 1];     %[In:Abundant, In:Low, Out:High, (1), AND]
rule19 = [4 4 6 1 1];     %[In:Abundant, In:Moderate, Out:Very High, (1), AND]
rule20 = [4 5 6 1 1];     %[In:Abundant, In:High, Out:Very High, (1), AND]
rule21 = [4 6 7 1 1];     %[In:Abundant, In:Very High, Out:Guaranteed, (1), AND]
rule22 = [5 2 5 1 1];     %[In:Eden, In:Very Low, Out:High, (1), AND]
rule23 = [5 3 6 1 1];     %[In:Eden, In:Low, Out:Very High, (1), AND]
rule24 = [5 4 6 1 1];     %[In:Eden, In:Moderate, Out:Very High, (1), AND]
rule25 = [5 5 7 1 1];     %[In:Eden, In:High, Out:Guaranteed, (1), AND]
rule26 = [5 6 7 1 1];     %[In:Eden, In:Very High, Out:Guaranteed, (1), AND]

%rule list, placing the individual ARRAYS into a MATRIX
firstSurviveCheckRuleList = [ rule1; rule2; rule3; rule4; rule5; rule6; rule7; rule8; rule9; rule10; 
    rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19; rule20; rule21; rule22; 
    rule23; rule24; rule25; rule26 ];

%addrule passes the rulesList into out FIS (a).
fis4 = addRule(fis4, firstSurviveCheckRuleList);
%Display the rules of the FIS.
showrule(fis4)


%DATA OUTPUT - loop to run through the data, then output & write results.
for i=1:size(inputData, 1)
    %var output to hold result of EVALFIS for the first 2 columns of INPUT data at row i in the excel document.
    output = evalfis([inputData(i, 7), inputData(i, 8)], fis4);
    %prints to console window, shows input values being fed into system.
    fprintf('%d) In(1): %.2f, In(2) %.2f => Out: %.2f \n\n', i, inputData(i, 7), inputData(i, 8), output);
    %write to result of FIS1 to InputData column E.
    xlswrite('InputData.xlsx', output, 1, sprintf('I%d', i + 1));
end

end