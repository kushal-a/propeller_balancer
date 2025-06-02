x = [-8 -7 -6 -5 -4 -3 -2 -1 0 1 2 3 4 5 6 7 8]/7;
y = zeros(1,13);

for i = 1:17
    y(i) = sign(x(i))*saturate(abs(x(i)),0.7);
end

plot(x,y)

function r = saturate(r,alpha)

    % Let r be any number. When r>alpha (some ratio), we want r to
    % saturate to 1 exponentially

    % Let r' be corrected r. For r>alpha let r' = a - b*exp(-c*r)
    % Using continuity and differentiability we calculate a,b,c
    if (r>alpha)
        a = 1;
        c = 1/(1-alpha);
        b = exp(c*alpha)/c;

        r = a-b*exp(-c*r);

    end
end