A=load('stoneColumn_b/postProcessing/Profiles/6.6/Profile2_p_tauXZ.xy');
A1=load('stoneColumn_b/postProcessing/Profiles/13.2/Profile2_p_tauXZ.xy');
%A(:,2)=A(:,2)/23643.45639;
%A1(:,3)=-A1(:,3)/23643.45639;
A(:,2)=A(:,2)/A(1,2);
A1(:,3)=-A1(:,3)/A(1,2);
A1(2,:)=[];
figure(1)
plot(A(:,2),A(:,1),'linewidth',2)
figure(2)
plot(A1(:,3)/23643.45639,A1(:,1),'linewidth',2)


B=load('SumerExample_b/postProcessing/Profiles/6.6/Profile2_p_tauXZ.xy');
B1=load('SumerExample_b/postProcessing/Profiles/13.2/Profile2_p_tauXZ.xy');
B
B1
B(2,:)=[];
B1(2,:)=[];
B(:,2)=B(:,2)/B(1,2);
B1(:,3)=-B1(:,3)/B(1,2);
figure(1)
hold on
plot(B(:,2),B(:,1),'linewidth',2)
hold off
l1=legend('Case 3','Case 2','Location','northwest')
x1=xlabel('p/p0')
y1=ylabel('z/h')
set(x1, 'FontSize', 20)
set(y1, 'FontSize', 20)
set(l1, 'FontSize', 20)
set(x1,'FontWeight','bold')
set(y1,'FontWeight','bold')
set(gca,'FontSize',20)

saveas(figure(1),'pressure_case23.png')
figure(2)
hold on
plot(B1(:,3)/-B1(1,2),B1(:,1),'linewidth',2)
hold off


l2=legend('Case 3','Case 2')
x2=xlabel('\tau_{XZ}/p0','Interpreter','tex')
y2=ylabel('z/h')
set(x2, 'FontSize', 20)
set(y2, 'FontSize', 20)
set(l2, 'FontSize', 20)
set(x2,'FontWeight','bold')
set(y2,'FontWeight','bold')
set(gca,'FontSize',20)

saveas(figure(2),'stress_case23.png')

