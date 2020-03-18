function [Y, drop] = Compress(X, tol)
% Block size
b_size = 8;
[row_size, col_size] = size(X);
Y = zeros(row_size, col_size);
drop_count = 0;

for i = 1:b_size:row_size
    for j = 1:b_size:col_size
        % For each block in original picture
        subblock = X(i:i+b_size-1, j:j+b_size-1);
        dtf2_block = fft2(subblock);
        dft2_abs = abs(dtf2_block);
        threshold = tol * max(dft2_abs(:));
        % Drop
        for k = 1:b_size
            for l = 1:b_size
                if dft2_abs(k,l) < threshold
                    % Satisfy the condition, drop the DFT value of this pixel
                    dtf2_block(k,l) = 0;
                    drop_count = drop_count + 1;
                end
            end
        end
        new_block = ifft2(dtf2_block);
        Y(i:i+b_size-1, j:j+b_size-1) = real(new_block);
    end
end
% return drop ratio
drop = double(drop_count)/double(row_size*col_size);
end
