%% Fourier Transform Data
% clc; clear; close all;
% CPU = [256, 1024, 2048;
%        1.566, 40, 50];
% MPI = [256, 1024, 2048;
%        0.9, 13, 16];
% CUDA = [256, 1024, 2048;
%        0.3, 0.8, 1.5];
%    
clc; clear; close all;
CPU = [128, 256, 512, 1024, 2048;
       0.148355, 1.58998,15.2248, 134.881,1243.01];
MPI = [128, 256, 512, 1024, 2048;
        0.477474, 1.22748, 8.2331, 69.6758, 595.861];
CUDA = [128, 256, 512, 1024, 2048;
        0, 1, 1, 2, 6];   
%% CPU
close all;
plot([CPU(1,:)], [CPU(2,:)],'b--o')

title('Performance of 2D Fourier Transform using Thread')
xlabel('Size (NxN)')
ylabel('Time (s)')

legend('Thread')    
    
%% MPI
close all;
plot([MPI(1,:)], [MPI(2,:)],'k--o')

title('Performance of 2D Fourier Transform using MPI')
xlabel('Size (NxN)')
ylabel('Time (s)')

legend('MPI')  
%% CUDA
close all;
plot([MPI(1,:)], [CUDA(2,:)],'r--o')

title('Performance of 2D Fourier Transform using CUDA')
xlabel('Size (NxN)')
ylabel('Time (s)')

legend('CUDA')  

%% Results DFT
plot([CPU(1,:)], [CPU(2,:)],'b--o',[MPI(1,:)], [MPI(2,:)],'k--o', [CUDA(1,:)], [CUDA(2,:)], 'r--o')

title('Performance of 2D Fourier Transform using Thread, MPI, and CUDA ')
xlabel('Size (NxN)')
ylabel('Time (s)')

legend('Thread','MPI', 'CUDA')


