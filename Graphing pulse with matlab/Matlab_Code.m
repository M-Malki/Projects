s = serial('COM3');             %Start serial communications with port COM3
s.BaudRate = 9600;              %Arduino's Baud Rate
fopen(s)                        %Open the serial
A=zeros(1,1000);                %A will store the recived data
fBuffer = fscanf(s,'%u')';      %Scan multiple times to emptey the serial buffer
fBuffer = fscanf(s,'%u')';
fBuffer = fscanf(s,'%u')';
for i = 1:2000                  %This loop will run the program for a specific number of data frames
fBuffer = fscanf(s,'%u')';      %Move data from serial buffer to the frame buffer (fBuffer)
A=[A fBuffer(1:10)];            %Add the recived frame to the end of the data array
A=A(11:1010);                   %Shift left by one frame
plot(A)                         %Plot the recived data array
axis([70 1000 450 750])         %Adjust the axies 
pause(0.001);                   
end
fclose(s);                      %Close the serial 