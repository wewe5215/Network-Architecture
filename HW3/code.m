load('network_A.mat')
%rec[0][x] --> check if the node is in the tree
rec = zeros(2,100);

for i = 1 : 100%check the nodes connected to the root(1)
    if(A(1,i) == 1)
        rec(1,i) = 1;%the first layer
        rec(2,i) = 1;%i is connected to 1
    end
end

for layer = 1 : 100
    for i = 1 : 100
%ensure that the tree is constructed instead of a lonely node
        if(rec(1,i) == layer)
            for j = 1 : 100
                if(rec(2,j) == 0 && A(i,j) == 1)
                     rec(1,j) = layer+1;
                     rec(2,j) = i;
                
                end
         
               
            end

        end
    end
end
%write back
tree = zeros(100,100);
for i = 1 : 100
    tree(i, rec(2,i)) = 1;
    tree(rec(2,i), i) = 1;
end
save('result.mat','tree');
