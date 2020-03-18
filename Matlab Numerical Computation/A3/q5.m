%{
1) this code first plot the sound, transform the sound into frequency power
spectrum, zero out(filter out) the high frequency part, which is the bird sound,
and lastly convert back the spectrum to sound, which only contains the train 
whistle.

2) the frequency threshold i used is 2200.

3) similarities: It looks like a smaller bubble followed by a big bubble.
    differences: In noisy signals, there are a lot of spikes on both
                        bubbles, while there are none on denoised signals.

%}
% Load Input Data 
load('train_bird.mat');
y_len = length(y);

% Plot Input Signal
subplot(2, 2, 1);
plot(y);
title('Original Input');
xlabel('Time');

% Calculate DFT
dft_y = fft(y);

% Plot Power Spectrum
subplot(2, 2, 2);
stem(abs(dft_y));
title('Power Spectrum of Original Input');
xlabel('Frequency');

% zero out the bird sound(filter)
cut = 2200;
dft_train = dft_y;
dft_train(cut+1: y_len-cut-1) = 0;

subplot(2, 2, 4);
stem(abs(dft_train));
title('Power Spectrum of Train Whistle');
xlabel('Frequency');

%Convert back to train whistle
y_train = ifft(dft_train);
subplot(2, 2, 3);
plot(real(y_train));
title('Train Whistle', 'FontSize', 8);
xlabel('Time');
sound(real(y_train), Fs);