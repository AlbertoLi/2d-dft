%% File IO
clc; clear; close all;
filename = 'Tower2048.txt';
fprintf("Opening file '%s'...\n",filename);
fid = fopen(filename);
tline = fgetl(fid);


mySize = str2num(tline);
tline = fgetl(fid);
X = zeros(mySize(1), mySize(2));

row = 1;
while ischar(tline)
    line = tline;
    arr = str2num(line);
    X(row,:) = arr;
    tline = fgetl(fid);
    row = row + 1;
end
fclose(fid);


%% 2D FFT
fprintf('Calculating FFT\n');
Y = fft2(X);

%% Write to file
out_file = 'results.txt';
fprintf("Writing to file '%s...'\n",out_file);
dlmwrite(out_file,Y,'delimiter',',');
fprintf("Successfully finished writing to file!\n",out_file);

