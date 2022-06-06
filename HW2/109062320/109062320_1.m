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

