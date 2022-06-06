
load("inputdata.mat")
cx = [1 0 0 0 0 0 1 0 0 1 1 0 0 0 0 0 1 0 0 0 1 1 1 0 1 1 0 1 1 0 1 1 1];
mx = [packet, zeros(1, 32)];
%mx = bitshift(packet, 32);
rx = [];
for i = 1 : 12000
    if mx(i) == 1
        %if the first one is 0,add the last one and continue to calc
        rx(1 : 32) = xor(mx(i+1 : i+32), cx(2:33));%cx[1] is always 1
        mx(i+1 : i+32) = rx(1 : 32);
    end
end
codepacket = [packet(1 : 12000), mx(12001 : 12032)];%can't use rx(1 : 32)

error=zeros(1,12032);
rx1=ones(1,32);
for i=1:12032
   for j=i+2:2:12032

        for k=i+4:4:12032
            for l=i+9:10:12032
                
               error=zeros(1,12032);
               error(i)=1; 
               error(j)=1; 
               error(k)=1; 
               error(l)=1;
               
               for x=1:12000
                   if error(x)==1
                       rx1(1:32)=xor(error(x+1:x+32),cx(2:33));
                       error(x+1:x+32)=rx1(1:32);
                       
                   end
               end
               temp = sum(rx1);
               temp
               if sum(rx1)==0
                   break;
               end
               
            end
            if sum(rx1)==0
                   break;
            end
            
        end
        if sum(rx1)==0
            break;
        end
       
    end
    if sum(rx1)==0
       break;
    end
end
%the above calculation will change error
error=zeros(1,12032);
error(i)=1; 
error(j)=1; 
error(k)=1; 
error(l)=1;
save('s109062320.mat','codepacket','error');

