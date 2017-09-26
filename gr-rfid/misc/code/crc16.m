% Input
Input = [1 0 1 0 1 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 1 0]';
k = length(Input);
h = crc.generator;
% Remainder of step 1)
cw1 = generate(h,[ones(16, 1); zeros(k-16,1)]);
% Remainder of step 2)
cw2 = generate(h,Input);
% Add the remainders and complement:
Workaround_FCS = not(mod(cw1(end-16+1:end) + cw2(end-16+1:end),2))'