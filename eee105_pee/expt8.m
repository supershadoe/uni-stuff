f = logspace(1, 5);
w = 2 * pi .* f;
r = 30;
l = 0.7e-3;
c = 1.5e-6; % capacitive
% c = 15.5e-3; % inductive
% c = 1 ./ (w .* w .* l); % resistive
xc = 1./(1i .* w .* c);
xl = 1i .* w .* l;
hf = xc ./ (xc + xl + r);
subplot(211);
loglog(f, abs(hf));
title('Magnitude');
xlabel('Frequency (Hz)');
ylabel('Amplitude');
axis([10 1e5 1e-3 10]);
subplot(212);
semilogx(f, angle(hf));
title('Phase');
xlabel('Frequency (Hz)');
ylabel('Angle (rad)');
axis([10 1e5 -3.5 0.5]);