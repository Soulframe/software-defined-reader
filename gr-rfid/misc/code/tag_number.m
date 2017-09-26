input1 = x_1(5.44e5:5.48e5);
input2 = x_1(5.62e5:5.68e5);
x = [real(input1);real(input2)];
y = [imag(input1);imag(input2)];
figure;
plot(y./x)
