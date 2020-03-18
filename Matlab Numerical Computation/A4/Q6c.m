load('uwaterloo.mat');

spy(G);
title('Sparsity Pattern of G');
xlabel('Page going to');
ylabel('Page coming from');

alpha = 0.85;
[p, iter] = PageRank(G, alpha);
[y, I] = sort(p, 'descend');
for n = 1:min(length(I), 20)
    disp([num2str(n) ': '  U{I(n)}]);
end