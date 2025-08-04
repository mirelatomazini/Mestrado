
filePath = 'G:\Testes\Teste_Somador_Manufaturado_AD826';

% 1. Import the Data
opts = detectImportOptions('scope_38.csv'); % Adjust filename as needed
opts.DataLines = [3 inf]; % Assuming data starts from row 6, adjust if necessary
data = readmatrix('scope_38.csv', opts);

time = data(:,1); % Assuming time is in the first column
signal = data(:,2); % Assuming signal amplitude is in the second column

% 2. Determine Sampling Parameters
Ts = mean(diff(time)); % Sampling interval
Fs = 1/Ts; % Sampling frequency
Fn = Fs/2; % Nyquist frequency
L = length(signal); % Length of the signal

% 3. Prepare the Signal for FFT
signal_processed = signal - mean(signal); % Remove DC offset

% 4. Perform the FFT
Y = fft(signal_processed) / L; % Normalize the FFT

% 5. Create the Frequency Vector
Fv = linspace(0, Fn, floor(L/2)+1); % Frequency vector for positive frequencies

% 6. Analyze and Plot the Results
P2 = abs(Y(1:floor(L/2)+1)); % Single-sided amplitude spectrum
P2(2:end-1) = 2*P2(2:end-1); % Double the amplitude for non-DC, non-Nyquist components

figure;
plot(Fv, P2);
xlabel('Frequência (Hz)');
xscale('log')
ylabel('Amplitude');
title('FFT dos dados medidos no osciloscópio');
grid on;
saveas(gcf,'FFT_scope38.png')

