load('network_A.mat')
d = zeros(100, 100);
%trace from node 1 to node 100
for n = 1 : 100
    
    %use a table to record if there is a road to the destinated node or not
    table = zeros(2, 100);
    table(1, n) = 1;%we don't need to calculate the distance between the node to itself
    for i = 1 : 100
        
        if(i == n)
            continue;
        end
        
        if(A(n : i) == 1) %there is a road
            table(1, i) = 1;
            table(2, i) = 1; %table(2, 1) = A(n, i)

        end
    end
    %solve it by link state
    for now = 2 : 100 %iteration 2 to 100, 1 has already recorded

        for i = 1 : 100
            
            if(table(2,i) == now - 1) %what we want to found is the one in the last iteration to expand the range
                for j = 1: 100
                
                    if(A(i, j) == 1 && table(1, j) == 0) %to prevent from getting the wrong distance
                        
                        table(1, j) = 1;
                        table(2, j) = now;

                    end
                end
            end
        end

    end

    for i = 1 : 100
        d(n, i) = table(2, i);
    end
    

end
save('result.mat','d');
