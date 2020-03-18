% the order of importance is 6, 1, 7, 3, 4, 5, 2 
% in decreasing order
G = sparse(7, 7);
G(1, 6)=1;
G(2, 5)=1;
G(3, 1)=1;
G(3, 2)=1;
G(4, 1)=1;
G(5, 4)=1;
G(6, 5)=1;
G(6, 7)=1;
G(7, 2)=1;
G(7, 3)=1;
G(7, 4)=1;
[p, iter] = PageRank(G, 0.85);

subplot(1, 2, 1);
bar(p);
title('PageRank Score');
xlabel('Page Number');
ylabel('Score');

subplot(1, 2, 2);
spy(G);
title('Sparsity Pattern of G');
xlabel('Page going to');
ylabel('Page coming from');

