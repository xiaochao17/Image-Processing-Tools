k1 = -0.3536;
k2 = 0.1730;

ul = 1072;
vl = 712;

fx = 600;
fy = 600;

u = -ul/2+1:ul/2;
v = -vl/2+1:vl/2;

x1 = u/fx;
y1 = v/fy;

count = 1;
X = zeros(length(x1)*length(y1),2);
x_ori = zeros(length(x1)*length(y1),1);
y_ori = zeros(length(x1)*length(y1),1);

for xi = 1:length(x1)
    for yi = 1:length(y1)
      x = x1(xi);
      y = y1(yi);
      r_2 = x^2+y^2;
      xd = x*(1+k1*r_2+k2*r_2^2);
      yd = y*(1+k1*r_2+k2*r_2^2);
%       X(count,:) = [xd;yd];
%       x_ori(count) = x;
%       y_ori(count) = y;
      
      X(count,:) = [x;y];
      x_ori(count) = xd;
      y_ori(count) = yd;
      
      count = count+1;
    end
end
  
mdl_xd = fitlm(X, x_ori);
mdl_yd = fitlm(X, y_ori);

xp = mdl_xd.Coefficients.Estimate;
yp = mdl_yd.Coefficients.Estimate;

row = 1072;
col = 712;
fin=fopen('classroom.raw','r');
I=fread(fin,row*col,'uint8=>uint8'); 
Z=reshape(I,row,col);
% Z=Z';

x_result = zeros(ul*vl,1);
y_result = zeros(ul*vl,1);
count = 1;
for xi = 1:length(x1)
    for yi = 1:length(y1)
        x = x1(xi);
        y = y1(yi);
        r_2 = x^2+y^2;
        xd = x*(1+k1*r_2+k2*r_2^2);
        yd = y*(1+k1*r_2+k2*r_2^2);
        x_result(count) = (xp(1)+xp(2)*xd+xp(3)*yd)*fx+ul/2;
        y_result(count) = (yp(1)+yp(2)*xd+yp(3)*yd)*fy+vl/2;
        count = count+1;
    end
end

Z2 = zeros(ul,vl);
count = 1;
for i = 1:ul
    for j = 1:vl
        Z2(i,j) = Z(floor(x_result(count)),floor(y_result(count)));
        count = count+1;
    end
end
        
Z2 = Z2';
% k = imshow(Z');
k=imshow(Z2,[]);


