load('uwaterloo.mat');

alpha = [0.15 0.35 0.55 0.75 0.95];
for m = 1:length(alpha)
    disp(alpha(m));
    [p, iter] = PageRank(G, alpha(m));
    disp(iter);
    [y I] = sort(p, 'descend');
    for n = 1:min(length(I), 20)
        disp([num2str(n) ': '  U{I(n)}]);
    end
end