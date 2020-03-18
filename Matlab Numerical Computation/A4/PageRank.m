function [p, iter] = PageRank(G, alpha)
tol = 0.0000001;
% Make Sparse Matrix P, d
[P, d, p, e] = initialize(G);
% Get size of matrix G
[R, C] = size(G);
% Iterate
p_last = p;
iter = 0;
while 1
    p = alpha*(P*p+e*(transpose(d)*p)/R)+(1-alpha)*e/R;
    iter = iter + 1;
    % Check
    p_diff = abs(p - p_last);
    if max(p_diff(:,1)) < tol
        break;
    end
    p_last = p;
end