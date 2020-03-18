%{
    even with an extremely low tolerance, such as 0.00001, the image can be
    compressed by 10%. But with increasing tolerance, the percentage that 
    the image is compressed increases with a decreasing acceleration. in other
    words, the return of puting more effort into compressing the image
    dinimishies. 
    It is interesing that after losing 90% of a image, the image can still
    look good.
%}
X = imread('mountain.jpg');
X = im2double(X);
drop_ratio = double(zeros(1, 4));
nms_error = double(zeros(1, 4));

figure(1);

% Drop = 0.1
[Y, drop] = Compress(X, 0.00001);
Y(:,:) = min(Y(:,:), 1.0);
Y(:,:) = max(Y(:,:), 0.0);
subplot(2, 2, 1);
imshow(Y);
title('Drop ratio = 0.1 & tol = 0.00001');
drop_ratio(1) = drop;
nms_error(1) = sqrt(mean2((Y-X).^2)/(mean2(X).^2));

% Drop = 0.45
[Y, drop] = Compress(X, 0.004354);
Y(:,:) = min(Y(:,:), 1.0);
Y(:,:) = max(Y(:,:), 0.0);
subplot(2, 2, 2);
imshow(Y);
title('Drop ratio = 0.45 & tol = 0.004354');
drop_ratio(2) = drop;
nms_error(2) = sqrt(mean2((Y-X).^2)/(mean2(X).^2));

% Drop = 0.75
[Y, drop] = Compress(X, 0.02722);
Y(:,:) = min(Y(:,:), 1.0);
Y(:,:) = max(Y(:,:), 0.0);
subplot(2, 2, 3);
imshow(Y);
title('Drop ratio = 0.75 & tol = 0.02722');
drop_ratio(3) = drop;
nms_error(3) = sqrt(mean2((Y-X).^2)/(mean2(X).^2));

% Drop = 0.9
[Y, drop] = Compress(X, 0.07496);
Y(:,:) = min(Y(:,:), 1.0);
Y(:,:) = max(Y(:,:), 0.0);
subplot(2, 2, 4);
imshow(Y);
title('Drop ratio = 0.9 & tol = 0.07496');
drop_ratio(4) = drop;
nms_error(4) = sqrt(mean2((Y-X).^2)/(mean2(X).^2));

% Plot normalized mean square error
figure(2);
plot(drop_ratio, nms_error);
title('Error vs Drop Ratio');
xlabel('Drop Ratio');
ylabel('Error');