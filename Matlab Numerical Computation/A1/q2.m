function [ p_n ] = cal( n )
digits(7);
count = 1;
save0 = 1;
save1 = 0;
while (count <= n )
    if count == 1
        save1 = 1;
    elseif count == 2
        save1 = vpa(4/7)-0.0000001;
    else
        temp = -41/14 * save1 + 2 * save0;
        save0 = save1;
        save1 = temp;
    end
    count = count + 1;
end
p_n = save1;
return

