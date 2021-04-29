function FIS_3
%first clear the screen.
%clc;
%var to hold excel file.
data1 = ('Data.xlsx');
%read data from xls file and store in testData.
inputData = xlsread(data1);

%{
FIS::3.1 - Energy Available & Oxygenation Checks.
Input: Heat(Output::FIS::2.1), Depth(Input::FIS::1.1)
Output: Energy, Oxygen.
%}
%new Fuzzy Inference System called 'Energy & Oxygen Check'.
fis3 = newfis('Energy & Oxygen Check', 'DefuzzificationMethod', 'mom', 'AndMethod', 'min', ...
                                      'ImplicationMethod', 'prod', 'AggregationMethod', 'max')

%declare 'Depth' INPUT variable.
fis3 = addvar(fis3, 'input', 'Depth (m)', [-600 0]);
%declare MFs for Depth input.
fis3 = addmf(fis3, 'input', 1, 'The Trenches', 'zmf', [-450 -400]);
fis3 = addmf(fis3, 'input', 1, 'The Abyss', 'gbellmf', [100 5 -350]);
fis3 = addmf(fis3, 'input', 1, 'Midnight Zone', 'gbellmf', [70 5 -200]);
fis3 = addmf(fis3, 'input', 1, 'Twilight Zone', 'gbellmf', [45 5 -95]);
fis3 = addmf(fis3, 'input', 1, 'Sunlight Zone', 'gbellmf', [30 5 -30]);
fis3 = addmf(fis3, 'input', 1, 'The Surface', 'smf', [-20 0]);
%declare 'Heat Level' INPUT variable.
fis3 = addvar(fis3, 'input', 'Heat Level (c)', [-5 50]);
%declare MFs for Heat Levels input variable.
fis3 = addmf(fis3, 'input', 2, 'Freezing', 'trapmf', [-5 -5 0 0]); 
fis3 = addmf(fis3, 'input', 2, 'Cold', 'trapmf', [0 0.5 4.5 6]); 
fis3 = addmf(fis3, 'input', 2, 'Cool', 'pimf', [4 6 9 12]);
fis3 = addmf(fis3, 'input', 2, 'Temperate', 'gbellmf', [5 4 15]);
fis3 = addmf(fis3, 'input', 2, 'Warm', 'gbellmf', [6 4 24]);
fis3 = addmf(fis3, 'input', 2, 'Hot', 'gbellmf', [5 4 34]);
fis3 = addmf(fis3, 'input', 2, 'Very Hot', 'smf', [35 40]); 
%declare the OUTPUT variable 'Energy Available'.
fis3 = addvar(fis3, 'output', 'Energy Available (J)', [0 1000]);
%declare MFs for Energy output variable.
fis3 = addmf(fis3, 'output', 1, 'Barren', 'zmf', [10 100]);             %was 50/250 too much for barren
fis3 = addmf(fis3, 'output', 1, 'Sparse', 'gbellmf', [135 4 200]);  	%was too steep at 5, not enough cross over, back to 4. //was 200/2/225 shifted after change to barren, 2 to 4 to steeped curve into moderate as was leaking to far along the graph.
fis3 = addmf(fis3, 'output', 1, 'Moderate', 'gbellmf', [150 4 480]);    %same as above // was 200/2/500 - needed 2-5 as needed to steepen curves, tails reaching too far.
fis3 = addmf(fis3, 'output', 1, 'Abundant', 'gbellmf', [145 4 760]);    %same as above // was 200/2/775 - similar reasons for change as above.
fis3 = addmf(fis3, 'output', 1, 'Eden', 'smf', [850 950]);              %same as above // was 750/950 - 750 reached too far back to be 'eden'
%declare the OUTPUT variable 'Oxygenation Rate'.
fis3 = addvar(fis3, 'output', 'Oxygenation Rate (%)', [0 100]);
%declare MFs for Oxygen output variable.
fis3 = addmf(fis3, 'output', 2, 'Death Zone', 'zmf', [0.25 1]); %reduced from 2/8
fis3 = addmf(fis3, 'output', 2, 'Very Low', 'gbellmf', [12 2.5 10]);
fis3 = addmf(fis3, 'output', 2, 'Low', 'gbellmf', [14 3 30]);
fis3 = addmf(fis3, 'output', 2, 'Moderate', 'gbellmf', [14 3 55]);
fis3 = addmf(fis3, 'output', 2, 'High', 'gbellmf', [14 3 78]);
fis3 = addmf(fis3, 'output', 2, 'Very High', 'smf', [83 92]);

%RULES(37) In:DEPTH(6), In:HEAT(7), Out:ENERGY(5), Out:OXYGEN(6), Weight=1, (AND) // 6 x 7 = 42. 
rule1  = [0 1 1 1 1 1];     %[In:Any, In:Freezing, Out:Barren, Out:Death Zone, (1), AND] %takes care of freezing, so 1 rule for 7.  
rule2  = [1 2 5 5 1 1];     %[In:The Trenches, In:Cold, Out:Eden, Out:High, (1), AND]
rule3  = [1 3 4 5 1 1];     %[In:The Trenches, In:Cool, Out:Abundant, Out:High, (1), AND]
rule4  = [1 4 4 3 1 1];     %[In:The Trenches, In:Temperate, Out:Abundant, Out:Moderate, (1), AND]
rule5  = [1 5 3 3 1 1];     %[In:The Trenches, In:Warm, Out:Moderate, Out:Moderate, (1), AND]
rule6  = [1 6 3 2 1 1];     %[In:The Trenches, In:Hot, Out:Moderate, Out:Low, (1), AND]
rule7  = [1 7 2 2 1 1];     %[In:The Trenches, In:Very Hot, Out:Sparse, Out:Low, (1), AND]
rule8  = [2 2 2 3 1 1];     %[In:The Abyss, In:Cold, Out:Sparse, Out:Low, (1), AND]
rule9  = [2 3 2 3 1 1];     %[In:The Abyss, In:Cool, Out:Sparse, Out:Low, (1), AND]
rule10 = [2 4 1 2 1 1];     %[In:The Abyss, In:Temperate, Out:Barren, Out:Very Low, (1), AND]
rule11 = [2 5 1 2 1 1];     %[In:The Abyss, In:Warm, Out:Barren, Out:Very Low, (1), AND]
rule12 = [2 6 1 2 1 1];     %[In:The Abyss, In:Hot, Out:Barren, Out:Very Low, (1), AND]
rule13 = [2 7 1 1 1 1];     %[In:The Abyss, In:Very Hot, Out:Barren, Out:Death Zone, (1), AND]
rule14 = [3 2 3 5 1 1];     %[In:Midnight Zone, In:Cold, Out:Moderate, Out:High, (1), AND]
rule15 = [3 3 3 4 1 1];     %[In:Midnight Zone, In:Cool, Out:Moderate, Out:Moderate, (1), AND]
rule16 = [3 4 2 4 1 1];     %[In:Midnight Zone, In:Temperate, Out:Sparse, Out:Moderate, (1), AND]
rule17 = [3 5 2 3 1 1];     %[In:Midnight Zone, In:Warm, Out:Sparse, Out:Low, (1), AND]
rule18 = [3 6 1 2 1 1];     %[In:Midnight Zone, In:Hot, Out:Barren, Out:Very Low, (1), AND]
rule19 = [3 7 1 2 1 1];     %[In:Midnight Zone, In:Very Hot, Out:Barren, Out: Very Low, (1), AND]
rule20 = [4 2 4 5 1 1];     %[In:Twilight Zone, In:Cold, Out:Adundant, Out:High, (1), AND]
rule21 = [4 3 4 5 1 1];     %[In:Twilight Zone, In:Cool, Out:Adundant, Out:High, (1), AND]
rule22 = [4 4 3 4 1 1];     %[In:Twilight Zone, In:Temperate, Out:Moderate, Out:Moderate, (1), AND]
rule23 = [4 5 3 4 1 1];     %[In:Twilight Zone, In:Warm, Out:Moderate, Out:Moderate, (1), AND]
rule24 = [4 6 2 3 1 1];     %[In:Twilight Zone, In:Hot, Out:Sparse, Out:Low, (1), AND]
rule25 = [4 7 1 3 1 1];     %[In:Twilight Zone, In:Very Hot, Out:Barren, Out:Low, (1), AND]
rule26 = [5 2 5 6 1 1];     %[In:Sunlight Zone, In:Cold, Out:Eden, Out:Very High, (1), AND]
rule27 = [5 3 4 5 1 1];     %[In:Sunlight Zone, In:Cool, Out:Abundant, Out:High, (1), AND]
rule28 = [5 4 4 5 1 1];     %[In:Sunlight Zone, In:Temperate, Out:Abundant, Out:High, (1), AND]
rule29 = [5 5 3 4 1 1];     %[In:Sunlight Zone, In:Warm, Out:Moderate, Out:Moderate, (1), AND]
rule30 = [5 6 3 3 1 1];     %[In:Sunlight Zone, In:Hot, Out:Moderate, Out:Low, (1), AND]
rule31 = [5 7 2 3 1 1];     %[In:Sunlight Zone, In:Very Hot, Out:Sparse, Out:Low, (1), AND]
rule32 = [6 2 5 6 1 1];     %[In:The Surface, In:Cold, Out:Eden, Out:Very High, (1), AND]
rule33 = [6 3 5 6 1 1];     %[In:The Surface, In:Cool, Out:Eden, Out:Very High, (1), AND]
rule34 = [6 4 4 5 1 1];     %[In:The Surface, In:Temperate, Out:Abundant, Out:High, (1), AND]
rule35 = [6 5 4 4 1 1];     %[In:The Surface, In:Warm, Out:Abundant, Out:Moderate, (1), AND]
rule36 = [6 6 3 3 1 1];     %[In:The Surface, In:Hot, Out:Moderate, Out:Low, (1), AND]
rule37 = [6 7 2 3 1 1];     %[In:The Surface, In:Very Hot, Out:Sparse, Out:Low, (1), AND

%rule list, placing the individual ARRAYS into a MATRIX
eneryOxygenLevelRuleList = [ rule1; rule2; rule3; rule4; rule5; rule6; rule7; rule8; rule9; rule10; 
    rule11; rule12; rule13; rule14; rule15; rule16; rule17; rule18; rule19; rule20; rule21; rule22; 
    rule23; rule24; rule25; rule26; rule27; rule28; rule29; rule30; rule31; rule32; rule33; rule34; 
    rule35; rule36; rule37 ];

%addrule passes the rulesList into FIS.
fis3 = addRule(fis3, eneryOxygenLevelRuleList);
%Display the rule
showrule(fis3)

%DATA OUTPUT - loop to run through the data, then output & write results.
for i=1:size(inputData, 1)
    %var output to hold result of EVALFIS for the first 2 columns of INPUT data at row i in the excel document.
    output = evalfis([inputData(i, 1), inputData(i, 6)], fis3);
    %prints to console window, shows input values being fed into system.
    fprintf('%d) In(1): %.2f, In(2) %.2f => Out: %.2f \n\n', i, inputData(i, 1), inputData(i, 6), output);
    %write to result of FIS1 to InputData column E.
    xlswrite('InputData.xlsx', output, 1, sprintf('G%d', i + 1));
end

end