clear
close all

[x,fs]=audioread('Babble_0_s0_n180.wav'); %% Any 2 mic Signal
x1=vertcat(x,x,x);
x=x1';

[nmic, nn] = size(x);
if ~exist('nfft','var')|isempty(nfft), nfft = 2048; end
if ~exist('eta','var')|isempty(eta), eta = 0.1; end
if ~exist('maxiter','var')|isempty(maxiter), maxiter = 500; end
if ~exist('tol','var')|isempty(tol), tol=1e-6; end
if ~exist('nsou','var')|isempty(nsou), nsou = nmic; end

win = 2*hanning(nfft,'periodic')/nfft;
winlen = size(win,1);
overlap = fix(0.5*nfft);
shift = winlen - overlap;
nframes = fix((nn+winlen)/shift)-1;
disp(nframes)
pObj = Inf;
epsi = 1e-6;
nfreq = fix(nfft/2)+1;
train_frames = 101;
x = [zeros(2, winlen/2) x];
X = zeros(nsou,fix(nfft));
Wp = zeros(nsou,nsou,nfreq);
dWp = zeros(size(Wp));
Q = zeros(nsou,nmic,nfreq);
Xp = zeros(nsou,train_frames,nfreq);
Xp_1=zeros(nmic,1,nfreq);
Xp_2=zeros(nmic,1,nfreq);
Xn = zeros(nsou,nfreq);
sp = zeros(nsou,nn+winlen+nfft);
S = zeros(nsou,train_frames,nfreq);
Ssq = zeros(nsou,nframes);
Ssq1 = zeros(nsou,nframes);
x_fft_final=zeros(nmic,(nfft/2)+1);
x_old=zeros(nmic,(nfft/2)+1);
k=1;
Xn_1=zeros(nmic,train_frames,(nfft/2)+1);
Xn_2=zeros(nmic,1,(nfft/2)+1);
sk = zeros(nmic,nn+winlen+nfft);
v=zeros(nmic,nn+winlen+nfft);
tic;
x_prev1=zeros(1024,1);
x_prev2=zeros(1024,1);
win2=(win.^2)';
v1prev=win2(1025: 2048)';
v2prev=zeros(1024,1);

x_in_prev=zeros(nmic,1024);
for n = 1:nframes
    %     tic
    sp = (n-1)*shift+1;
    if (n<train_frames+1)
        for m=1:nmic
            %             xwin(m,1:winlen)= win.*x(m,sp:sp+winlen-1)';
            xwin(m,1:nfft/2)= win(1:nfft/2).*x_in_prev(m,1:nfft/2)';
            x_in_prev(m,1:nfft/2)=x(m,sp:sp+nfft/2-1);
            xwin(m,(nfft/2)+1 : nfft)=win((nfft/2)+1 : nfft).*x(m,sp:sp+nfft/2-1)';
        end
        
        for m=1:nmic
            X(m,1:winlen)= conj(fft(xwin(m,:)));
            Xn(m,1:fix(nfft/2)+1) = X(m,1:fix(nfft/2)+1);
        end

        Xn_1(:,n,:)=Xn;
    else
        break;
    end
    
end


X=Xn_1;
N1 = size(X,2);

%Execute PCA and initialize
for k=1:nfreq
    
    Xmean = mean(X(:,:,k),2)*ones(1,train_frames);
    Rxx = (X(:,:,k)-Xmean)*(X(:,:,k)-Xmean)'/train_frames;
    [E, D] = eig(Rxx);
    
    d = real(diag(D));
    [tmp, order] = sort(-d);
    E = E(:,order(1:nsou));
    D = diag(real(d(order(1:nsou)).^-.5));
    Q(:,:,k) = D*E';
    Xp(:,:,k) = (Q(:,:,k))*(X(:,:,k)-Xmean);
    
    Wp(:,:,k) = eye(nsou);
end


for iter=1:maxiter 
    dlw = 0;
    for k=1:nfreq
        S(:,:,k) = Wp(:,:,k)*Xp(:,:,k);
    end
    Ssq = sum(abs(S).^2,3).^.5;
    Ssq1 = (Ssq+epsi).^-1;
    
    for k=1:nfreq
        % Calculate multivariate score function and gradients
        Phi = Ssq1.*S(:,:,k);
        dWp(:,:,k) = (eye(nsou) - Phi*S(:,:,k)'/train_frames)*Wp(:,:,k);
        dlw = dlw + log(abs(det(Wp(:,:,k)))+epsi);
    end
    
    % Update unmixing matrices
    Wp = Wp + eta*dWp;
    
    Obj = (sum(sum(Ssq))/train_frames-dlw)/(nsou*nfreq);
    dObj = pObj-Obj;
    pObj = Obj;
    
    if mod(iter,10) == 0
        fprintf('%d iterations: Objective=%e, dObj=%e\n',iter,Obj,dObj);
    end
    
    if abs(dObj)/abs(Obj) < tol, break; end
    
end

% Correct scaling of unmixing filter coefficients
for k=1:nfreq
    W(:,:,k) = Wp(:,:,k)*Q(:,:,k);
    W(:,:,k) = diag(diag(pinv(W(:,:,k))))*W(:,:,k);
end

n=toc;
k1=1;

len=2048;
len1=1024;len2=1024;

for n = 1:nframes
    tic
    count = n-train_frames;
    sp = (n-1)*shift+1;

        for m=1:nmic
            xwin(m,1:nfft/2)= win(1:nfft/2).*x_in_prev(m,1:nfft/2)';
            x_in_prev(m,1:nfft/2)=x(m,sp:sp+nfft/2-1);
            xwin(m,(nfft/2)+1 : nfft)=win((nfft/2)+1 : nfft).*x(m,sp:sp+nfft/2-1)';
        end
        
        for m=1:nmic
            X(m,1:winlen)= conj(fft(xwin(m,:)));
            Xn(m,1:fix(nfft/2)+1) = X(m,1:fix(nfft/2)+1);
        end
    
    Xn_2(:,:,:)=Xn;
    
    for k=1:nfreq
        S1(:,1,k) = W(:,:,k)*Xn_2(:,:,k);
    end
    
    for s=1:nmic
        Sq = squeeze(S1(s,:,:));
        X = [Sq;conj(Sq(end-1:-1:2,:))];
        tmp = real(ifft(conj(X)));
        xi_w=(win.*tmp(1:winlen))';
        if s==1
            xfinal1= x_prev1'+ xi_w(1:len1);
            win2=(win.^2)';
             v1 = v1prev'+ win2(1:len1);
            x_prev1= xi_w(len1+ 1: len)';
            v1prev = win2(len1+ 1: len)';
            xfinal11(k1:k1+ len2-1)=xfinal1./v1;
        else
            xfinal2= x_prev2'+ xi_w(1:len1);
            win2=(win.^2)';
            v2 = v1prev'+ win2(1:len1);
            x_prev2= xi_w(len1+ 1: len)';
            xfinal12(k1:k1+ len2-1)=xfinal2./v2;
        end         
    end 
        k1=k1+len2;  
        time= toc;
end
source1 = xfinal12;
source2 = xfinal11;