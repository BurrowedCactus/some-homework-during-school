function [P, d, p, e] = initialize(G)

[R, R] = size(G);
P = sparse(R, R);
d = sparse(R, 1);
p = sparse(ones(R, 1) / R);
e = sparse(ones(R, 1));

% For each node
for j = 1:1:R
    % sum the number of all links from node j
    link_num = full(sum(G(:,j)));
    % if node has links to other pages
    if link_num ~= 0
        for i = 1:1:R
            is_link = full(G(i, j));
            if is_link ~= 0
                P(i, j) = 1.0 / link_num;
            end
        end
    else
        % if node j is a dead end
        d(j, 1) = 1;
    end
end