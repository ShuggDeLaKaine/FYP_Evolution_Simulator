function FIS_1
%first clear the screen.
%clc;
%var to hold excel file.
data1 = ('Data.xlsx');
%read data from xls file and store in testData.
inputData = xlsread(data1);
%{
FIS::1.1 - Light Check.
Input: Depth, Pollutate
Output: Light.
%}
%new Fuzzy Inference System called 'Light Level Check'.
fis1 = newfis('Light Level Check', 'DefuzzificationMethod', 'mom', 'AndMethod', 'min', ...
                                    'ImplicationMethod', 'prod', 'AggregationMethod', 'max');

%declare 'Depth' INPUT variable.
fis1 = addvar(fis1, 'input', 'Depth (m)', [-600 0]);
%declare MFs for Depth input.
fis1 = addmf(fis1, 'input', 1, 'The Trenches', 'zmf', [-450 -400]);
fis1 = addmf(fis1, 'input', 1, 'The Abyss', 'gbellmf', [100 5 -350]);
fis1 = addmf(fis1, 'input', 1, 'Midnight Zone', 'gbellmf', [70 5 -200]);
fis1 = addmf(fis1, 'input', 1, 'Twilight Zone', 'gbellmf', [45 5 -95]);
fis1 = addmf(fis1, 'input', 1, 'Sunlight Zone', 'gbellmf', [30 5 -30]);
fis1 = addmf(fis1, 'input', 1, 'The Surface', 'smf', [-20 0]);
%declare 'Pollutant Present' INPUT variable.
fis1 = addvar(fis1, 'input', 'Pollutant Present (%)', [0 100]);
%declare MFs for Polluate Present input.
fis1 = addmf(fis1, 'input', 2, 'No Pollution', 'zmf', [0 3]);
fis1 = addmf(fis1, 'input', 2, 'Low Pollution', 'gbellmf', [17.5 3 15]);
fis1 = addmf(fis1, 'input', 2, 'Moderate Pollution', 'gaussmf', [15 50]);
fis1 = addmf(fis1, 'input', 2, 'High Pollution', 'gbellmf', [17.5 3 85]);
fis1 = addmf(fis1, 'input', 2, 'Complete Pollution', 'smf', [95 100]);
%declare the OUTPUT variable Light Level Check.
fis1 = addvar(fis1, 'output', 'Light Level (%)', [0 100]);
%declare MFs for Light Levels output variable.
fis1 = addmf(fis1, 'output', 1, 'No Light', 'trapmf', [0 0 0 1]);
fis1 = addmf(fis1, 'output', 1, 'Low Light', 'pimf', [0 0.5 30 55]);
fis1 = addmf(fis1, 'output', 1, 'Moderate Light', 'gaussmf', [15 55]);
fis1 = addmf(fis1, 'output', 1, 'High Light', 'pimf', [60 85 99 100]);
fis1 = addmf(fis1, 'output', 1, 'Complete Light', 'smf', [98 100]);

%RULES(18) In:DEPTH(5), In:POLLUTANT(6), Out:LIGHT(5), Weight=1, (AND) // 5 x 6 = 30 rules max 
rule1  = [1 0 1 1 1];  %[In:The Trenches, In:ANY Pollution, Out:No Light, (1), AND] = covers all 5 rules for The Trenches
rule2  = [2 5 1 1 2];  %[In:The Abyss, In:Complete Pollution, Out:No Light, (1), OR] = by using OR, covers above two rules - this single rule covers 9 possible rules.
rule3  = [3 1 2 1 1];  %[In:Midnight Zone, In:No Pollution, Out:Low Light, (1), AND]
rule4  = [3 2 1 1 1];  %[In:Midnight Zone, In:Low Pollution, Out:No Light, (1), AND]
rule5  = [3 3 1 1 1];  %[In:Midnight Zone, In:Moderate Pollution, Out:No Light, (1), AND]
rule6  = [3 4 1 1 1];  %[In:Midnight Zone, In:High Pollution, Out:No Light, (1), AND]
rule7  = [4 1 2 1 1];  %[In:Twilight Zone, In:No Pollution, Out:Low Light, (1), AND]
rule8  = [4 2 2 1 1];  %[In:Twilight Zone, In:Low Pollution, Out:Low Light, (1), AND]
rule9  = [4 3 1 1 1];  %[In:Twilight Zone, In:Moderate Pollution, Out:No Light, (1), AND]
rule10 = [4 4 1 1 1];  %[In:Twilight Zone, In:High Pollution, Out:No Light, (1), AND]
rule11 = [5 1 4 1 1];  %[In:Sunlight Zone, In:No Pollution, Out:High Light, (1), AND]
rule12 = [5 2 4 1 1];  %[In:Sunlight Zone, In:Low Pollution, Out:High Light, (1), AND]
rule13 = [5 3 3 1 1];  %[In:Sunlight Zone, In:Moderate Pollution, Out:Moderate Light, (1), AND]
rule14 = [5 4 2 1 1];  %[In:Sunlight Zone, In:High Pollution, Out:Low Light, (1), AND]
rule15 = [6 1 5 1 1];  %[In:The Surface, In:No Pollution, Out:Complete Light, (1), AND]
rule16 = [6 2 4 1 1];  %[In:The Surface, In:Low Pollution, Out:High Light, (1), AND]
rule17 = [6 3 4 1 1];  %[In:The Surface, In:Moderate Pollution, Out:High Light, (1), AND]
rule18 = [6 4 3 1 1];  %[In:The Surface, In:High Pollution, Out:Moderate Light, (1), AND]

%rule list, placing the individual ARRAYS into a MATRIX
lightLevelRuleList = [rule1; rule2; rule3; rule4; rule5; rule6; rule7; rule8; rule9; rule10; 
    rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18 ];

%addrule passes the rulesList into out FIS (a).
fis1 = addRule(fis1, lightLevelRuleList);
%Display the rules of the FIS.
showrule(fis1)

%DATA OUTPUT - loop to run through the data, then output & write results.
for i=1:size(inputData, 1)
    %var output to hold result of EVALFIS for the first 2 columns of INPUT data at row i in the excel document.
    output = evalfis([inputData(i, 1), inputData(i, 2)], fis1);
    %prints to console window, shows input values being fed into system.
    fprintf('%d) In(1): %.2f, In(2) %.2f => Out: %.2f \n\n', i, inputData(i, 1), inputData(i, 2), output);
    %write to result of FIS1 to InputData column E.
    xlswrite('InputData.xlsx', output, 1, sprintf('E%d', i + 1));
end

end