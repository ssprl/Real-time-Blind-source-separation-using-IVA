//
// Created by Abdullah on 9/4/2017.
//

#ifndef AUDIOTWOMICS_AUDIO_MAIN_H
#define AUDIOTWOMICS_AUDIO_MAIN_H
#define EPS 1.0e-7
#define FAC 3.051757812500000e-05f
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <jni.h>
//#include "audio_common.h"
#include "Transform.h"
#include <time.h>
#include "yeni.h"
#include "mvdr.h"
//#include "LogMMSE.h"
#include <android/log.h>
#include "mvdr2.h"
#include "fir.h"
#include "Transform.h"
#define FRAMESIZE 960
#define SAMPLINGFREQUENCY 16000
typedef struct Variables{
    // Timer* timer;
    double *topMicBuffer,*botMicBuffer, *outputBuffer,*output;
    int *originalBuffer;
    double *mixedBuffer;
    int stepSize,samplingRate,frameSize,filLen;
    float *y_curr, *y_prev, *e , *w, *y, u;
    int counter,uplimit;
    // float ake_counter,ake_timing, Threadtime, DurationTime;
    int angle_count;
    bool isEndFire,isOn;
    Transform *trans1;
    Transform *trans2;
    float ake_counter;
    float ake_avg_timer;
    double *filter_output1,*filter_output2,*prev_filter_output1,*prev_filter_output2;
    mvdr_parameters *mvdr;
    //logMMSE_parameters *logMMSE2; // for channel 2
}Variables;
int nFFT = 2048;
static double *noise_mean = (double*)calloc(nFFT, sizeof(double));
static double *noise_mu2 = (double*)calloc(nFFT, sizeof(double));
static double *sig2 = (double*)calloc(nFFT, sizeof(double));
static double *gammak = (double*)calloc(nFFT, sizeof(double));
static double *ksi = (double*)calloc(nFFT, sizeof(double));
static double *Xk_prev = (double*)calloc(nFFT, sizeof(double));
static double *log_sigma_k = (double*)calloc(nFFT, sizeof(double));
static double *noise_pow = (double*)calloc(nFFT, sizeof(double));
static double *vk = (double*)calloc(nFFT, sizeof(double));
static double *hw = (double*)calloc(nFFT, sizeof(double));
static double *evk = (double*)calloc(nFFT, sizeof(double));
static double *Lambda = (double*)calloc(nFFT, sizeof(double));
static double *pSAP = (double*)calloc(nFFT, sizeof(double));
static double* ensig = ( double *)calloc(nFFT, sizeof( double));
static double* HPF = ( double*)calloc(2*(nFFT), sizeof( double));
static double* H = ( double*)calloc((nFFT), sizeof( double));
static double *fftmagoutput = (double*)calloc(nFFT, sizeof(double));
//static double *phase = (double*)calloc(nFFT, sizeof(double));
//static double *h=(double*)calloc(nFFT,sizeof(double));
//long double* nsig = (long double *)calloc(nFFT, sizeof(long double));
double PRT;
double N;
double aa = 0.98;
double eta = 0.15;
double beta=2;
double max;
double ksi_min = (double)pow(10,((double)-25 /(double)10));
double sum_log_sigma_k = 0;
double vad_decision;
double qk = 0.3;
double qkr = (1 - qk) / qk;;
//double epsilon =  (double)pow(8.854,-12);
double epsilon = 0.001;
double total_noisepower=0;
double total_speechpower=0;
//double SNR_db;
char SNR_db_char;
int count=0;
int SPU = 0;
static double SNR_db;
//double *magnitudeLeft, *magnitudeRight, *phaseLeft, *phaseRight, *fifoOutput;
//double sum_ensig;
//double beta;
int on;
int frameCounter=0;
double snr_counter=0;
double sum_SNR=0;
double snr_avg;
Transform *X;
Transform *Y;
int k=1;


//static short *buffer = (short*)calloc(sourceBuffer.mDataByteSize/sizeof(short), sizeof(short));
//static short *output = (short*)calloc(sourceBuffer.mDataByteSize/sizeof(short), sizeof(short));
//static double *phase = (double*)calloc(nFFT, sizeof(double));
static double *input1 = (double*)calloc(FRAMESIZE, sizeof(double));
static double *float_output = (double*)calloc(nFFT, sizeof(double));
// static double *input1 = (double*)calloc(nFFT, sizeof(double));
// static double *store_buffer = (double*)calloc(FRAMESIZE, sizeof(double));
static double *output_final = (double*)calloc(FRAMESIZE, sizeof(double));
static double *output_old = (double*)calloc(FRAMESIZE, sizeof(double));
static double *in_buffer = (double*)calloc(nFFT, sizeof(double));
static double *in_prev = (double*)calloc(FRAMESIZE, sizeof(double));
//int DOA_fs = 16000;
//int DOA_NFFT = 2048;
//int DOA_n = 480;
short checkRange( double input );
double filter_weigth_endfire1[] = { 0.00379264875102451,0.00520050110158773,0.00406009793533778,0.00556320215187781,0.00432540932192198,0.00592528551797391,0.00458781950822409,0.00628615689486634,0.00484654907856365,0.00664521876799071,0.00510080323909524,0.00700187257482972,0.00534977241073830,0.00735552100732559,0.00559263277541438,0.00770557043542524,0.00582854683575284,0.00805143326793863,0.00605666447481720,0.00839252889043439,0.00627612854626025,0.00872826967002785,0.00648613976182934,0.00905771915936724,0.00669085908587920,0.00945817831849050,0.00703731126089307,0.00994215006233911,0.00737421046704226,0.0104080128810176,0.00768857075270549,0.0108560746959041,0.00797901484907073,0.0112858413651430,0.00824438820122947,0.0116968109079123,0.00848357968904206,0.0120885376912203,0.00869550038479636,0.0124606475566858,0.00887907963553519,0.0128128426523706,0.00903326656616235,0.0131449009488867,0.00915703732848403,0.0134566680538553,0.00924941282530959,0.0137480337255282,0.00930949861851928,0.0140188750213824,0.00933657525946878,0.0142689209446583,0.00933031314562544,0.0144974128760449,0.00929133356350317,0.0147021513272935,0.00922291634107478,0.0148762498229968,0.00913771270122310,0.0149925632194980,0.00910075999173297,0.0148421630913212,0.0126636313812859,0.0225174634589213,0.0142521747061476,0.0219871577311652,0.0137129082357324,0.0217166251555199,0.0130191316786209,0.0214920958276070,0.0122347303472432,0.0212918712557415,0.0113677904870717,0.0211174024136145,0.0104143159853925,0.0209781075335609,0.00936411368205822,0.0208892740596321,0.00820099608468276,0.0208730335364999,0.00690085220736288,0.0209612404717330,0.00542764453765448,0.0212009073639593,0.00372602499123588,0.0216643046343636,0.00170731669988241,0.0224687430467896,-0.000779005063869681,0.0238186816457776,-0.00400928857274738,0.0261061963676989,-0.00854987200054424,0.0301923798933528,-0.0157690384059024,0.0384126895465478,-0.0300254404840187,0.0601102266974105,-0.0766372916360470,0.217267339847248,0.406738634494966,-0.111643107775375,0.0522012864938142,-0.0497894365767720,0.0238166656687191,-0.0348697541905056,0.0128527597280668,-0.0284932039396983,0.00678258872250773,-0.0251593681381640,0.00277521830383064,-0.0232482677104772,-0.000163521608411945,-0.0221108135834854,-0.00247223916852858,-0.0214357675761618,-0.00437408824969214,-0.0210548806332054,-0.00599430172644423,-0.0208689598661899,-0.00740837637921708,-0.0208155135819822,-0.00866437928404160,-0.0208530254060181,-0.00979427040962799,-0.0209526573801734,-0.0108200977366217,-0.0210935492564283,-0.0117576447015144,-0.0212599170018133,-0.0126188529712873,-0.0214388608040862,-0.0134141484725320,-0.0216172087350245,-0.0141583099513488,-0.0217664335747066,-0.0149273310891792,-0.0213693897534318,-0.00888178069919023,-0.0153017606159663,-0.00886688733248536,-0.0151371733625840,-0.00902806531037599,-0.0149367017225314,-0.00915083555925017,-0.0147211498092868,-0.00923267696738899,-0.0144900789600773,-0.00927520890710035,-0.0142422555413908,-0.00928016752997055,-0.0139766619800253,-0.00924913821903267,-0.0136925471350427,-0.00918356876078122,-0.0133893921145288,-0.00908480420984094,-0.0130668748900590,-0.00895411617448513,-0.0127248418213646,-0.00879272514108259,-0.0123632852003120,-0.00860181738915733,-0.0119823252044863,-0.00838255799404414,-0.0115821949242222,-0.00813610114639452,-0.0111632272831345,-0.00786359903763218,-0.0107258420947588,-0.00756621068886696,-0.0102705287401204,-0.00724511545528296,-0.00979782455883571,-0.00690146280146083,-0.00931023523333462,-0.00660096994134421,-0.00896385198402842,-0.00640045235723788,-0.00863052739624592,-0.00618822387057108,-0.00829205578894523,-0.00596647727496948,-0.00794861722906344,-0.00573623842042918,-0.00760070591238150,-0.00549841076442810,-0.00724887556903705,-0.00525386002885462,-0.00689370177818951,-0.00500343014461243,-0.00653577087006522,-0.00474794748785610,-0.00617567462342356,-0.00448822209088805,-0.00581400675753894,-0.00422504782943507,-0.00545136015739922,-0.00395920218831368,-0.00508832448111128,-0.00369144582659237,-0.00472548401218126,-0.00342252203795507,-0.00436341569536575,-0.00315315615917952,-0.00400268699563039,-0.00288404686375778,-0.00364381768879269,-0.00261580116488181,-0.00328724383048403,-0.00234897257493487,-0.00293338591993895,-0.00208409973204047,-0.00258264916460891,-0.00182116113434643,-0.00223311477494730,-0.00155704047983155,-0.00188263810265229,-0.00129142879440722,-0.00153136140080646,-0.00102458479749689,-0.00117943697744503,-0.000756765207705016,-0.000827016354059077,-0.000488224743451518,-0.000474250689078437,-0.000219216523408531,-0.000121290937319121,5.00074031306308e-05,0.000231712041786122,0.000319195494540851,0.000584607387014025,0.000588096144639489,0.000937244144477418,0.000856457102718060,0.00128947119016780,0.00112402487639237,0.00164113719281739,0.00139054406551477,0.00199209075078283,0.00165575626172715,0.00234218194256814,0.00191939368323456,0.00269152145855695,0.00218285794067849,0.00304323619559531,0.00244857653634485,0.00339792494177106,0.00271608922949492,0.00375516908205647,0.00298485290201578,0.00411454508835348,0.00325430653637949,0.00447559508528993,0.00352380849530598,0.00483777143558411};
double filter_weigth_endfire2[] = { -0.00123664565537952,-0.00187356166511389,-0.00149693823820705,-0.00222961544024721,-0.00175572882739444,-0.00258477225514369,-0.00201309705011997,-0.00294076346169471,-0.00227211520646283,-0.00329994379292766,-0.00253308626855626,-0.00366195147860937,-0.00279546201762779,-0.00402637606905216,-0.00305868168298060,-0.00439279469252297,-0.00332213929423804,-0.00476070739241763,-0.00358513265762772,-0.00512955835898901,-0.00384692808418714,-0.00549878217574590,-0.00410677323409943,-0.00586780656176923,-0.00436389762634982,-0.00623605438737426,-0.00461751312644366,-0.00660294584839177,-0.00486681436463076,-0.00696790083201207,-0.00511097903718718,-0.00733034153457847,-0.00534916799386302,-0.00768969547727925,-0.00558052485831343,-0.00804539936503551,-0.00580417431876018,-0.00839690556250341,-0.00601921507602539,-0.00874370125904948,-0.00622467826082482,-0.00908544424841222,-0.00641892373153130,-0.00943019959506728,-0.00669064383056794,-0.00992204481389820,-0.00702858715624504,-0.0104054201915404,-0.00734294175880732,-0.0108721705083113,-0.00763312820477906,-0.0113216081367015,-0.00789799440954356,-0.0117532535131663,-0.00813633974174717,-0.0121667343049421,-0.00834694348279922,-0.0125617869632300,-0.00852856137910490,-0.0129382699507832,-0.00867991321373648,-0.0132961831483272,-0.00879966341324227,-0.0136356951634992,-0.00888639158542868,-0.0139571834413022,-0.00893854578180770,-0.0142612977127857,-0.00895436281888421,-0.0145490705812370,-0.00893171847193728,-0.0148221351725045,-0.00886780742899251,-0.0150832240656727,-0.00875833495912165,-0.0153375640649314,-0.00859494742573086,-0.0155980439522357,-0.00835360780039664,-0.0159157945954342,-0.00789663383540558,-0.0206363027664860,-0.0148519181384195,-0.0220690590043754,-0.0138854619301048,-0.0220276900445298,-0.0130719264164274,-0.0219115556077018,-0.0122277546614666,-0.0217846897631847,-0.0113221760242421,-0.0216688864776865,-0.0103394226063425,-0.0215807458635627,-0.00926468241722324,-0.0215384819392559,-0.00807991347279498,-0.0215651775797686,-0.00676073781307432,-0.0216921857845159,-0.00527237479567672,-0.0219642304590391,-0.00356302250590895,-0.0224481856402539,-0.00155195968334263,-0.0232495066422212,0.000893635009539455,-0.0245456657576721,0.00400817227321098,-0.0266615581171771,0.00824655212780552,-0.0302647129860586,0.0146208196290106,-0.0369824566043909,0.0259243723724512,-0.0521042635455902,0.0537128680885575,-0.108175312403357,0.276749152551390,0.357181515098127,-0.100980745655235,0.0715820793867922,-0.0374178010256160,0.0435932082919645,-0.0199405380557720,0.0334366007384178,-0.0114318520912846,0.0284366044499496,-0.00620655048110716,0.0256223008687138,-0.00255336173372739,0.0239311390151478,0.000220121206078067,0.0228881278639333,0.00244699275801088,0.0222486559137046,0.00430697644184223,0.0218736527309880,0.00590529107440995,0.0216780220811879,0.00730738205776202,0.0216066583832825,0.00855585744677802,0.0216222675987974,0.00967939417283783,0.0216987811473797,0.0106976513873183,0.0218177061918603,0.0116239255795566,0.0219663552492734,0.0124659951515899,0.0221382850430528,0.0132233496425656,0.0223415723937912,0.0138622716829352,0.0226953155734929,0.0134832067607435,0.0156679998114862,0.00850980724495003,0.0155086553014193,0.00866463302265943,0.0153265360157429,0.00880280282431408,0.0151154993576268,0.00890811044964517,0.0148839923970806,0.00897687409560798,0.0146339521619067,0.00900880102173777,0.0143656254030971,0.00900460215256279,0.0140788015418799,0.00896532036088346,0.0137731909987731,0.00889210809600760,0.0134485553738039,0.00878614737540952,0.0131047529384789,0.00864862118353172,0.0127417520056463,0.00848070492008379,0.0123596314069388,0.00828356584456001,0.0119585757899091,0.00805836551553961,0.0115388690316427,0.00780626304966639,0.0111008871652585,0.00752841813515742,0.0106450899822629,0.00722599451529431,0.0101720026525578,0.00690020664349096,0.00968193588142537,0.00655648255099346,0.00925193604038025,0.00635258947043672,0.00891593086245755,0.00615133055131621,0.00857307842075927,0.00594052226112076,0.00822494647032008,0.00572078367450876,0.00787218555120959,0.00549295142518503,0.00751537870639564,0.00525788223461196,0.00715510307150185,0.00501642695354661,0.00679193869327990,0.00476942443825405,0.00642646893681345,0.00451769940961113,0.00605927897391762,0.00426206136666457,0.00569095378367850,0.00400330382057422,0.00532207606609191,0.00374220362963354,0.00495322419845869,0.00347952036499494,0.00458497027886903,0.00321599568574207,0.00421787828293043,0.00295235216802259,0.00385249226957039,0.00268925217107263,0.00348927005645771,0.00242726996374009,0.00312862719136342,0.00216695945038788,0.00277097148783726,0.00190884020604497,0.00241601936425822,0.00165089863007818,0.00206053455613409,0.00139131877828208,0.00170420957466524,0.00113036866467796,0.00134718751150964,0.000868314086413959,0.000989612774141471,0.000605417623109006,0.000631629844876327,0.000341939756688694,0.000273383094260227,7.81395839449389e-05,-8.49832254046085e-05,-0.000185724546767661,-0.000443324940799204,-0.000449394419207082,-0.000801497902419511,-0.000712611341893134,-0.00115935792179496,-0.000975115552091362,-0.00151676069558389};
double filter_weigth_broadside1[] = {0.000224170043480069,-0.000200257493833188,0.000176405919906362,-0.000152607930386222,0.000128856199352170,-0.000105143457159052,8.14624814664232e-05,-5.78060883898099e-05,3.41671237504768e-05,-1.05384544022979e-05,-1.30870403875216e-05,3.67164775251783e-05,-6.03569786685396e-05,8.40156788166763e-05,-0.000107699734934259,0.000131416334632206,-0.000155172704926273,0.000178976121097764,-0.000202833915679580,0.000226753487589994,-0.000250742311441122,0.000274807947043443,-0.000298958049136212,0.000323200377368412,-0.000347542806560116,0.000371993337274799,-0.000396560106729673,0.000421251400079261,-0.000446075662108201,0.000471041509368616,-0.000496157742795505,0.000521433360849894,-0.000546877573229335,0.000572499815187096,-0.000598309762518544,0.000624317347262433,-0.000650532774172880,0.000676966538026991,-0.000703629441830999,0.000730532615994161,-0.000757687538548430,0.000785106056500711,-0.000812800408391687,0.000840783248165929,-0.000869067670468761,0.000897667237456483,-0.000926596007257229,0.000955868564219232,-0.000985500051078058,0.00101550620320701,-0.00104590338511864,0.00107670862940469,-0.00110793967831970,0.00113961502822833,-0.00117175397716194,0.00120437667575228,-0.00123750418183328,0.00127115851903566,-0.00130536273973073,0.00134014099271356,-0.00137551859605104,0.00141152211557993,-0.00144817944957727,0.00148551992018454,-0.00152357437223552,0.00156237528020324,-0.00160195686406559,0.00164235521497592,-0.00168360843173200,0.00172575676914671,-0.00176884279956351,0.00181291158889434,-0.00185801088874567,0.00190419134637606,-0.00195150673445120,0.00200001420282941,-0.00204977455487480,0.00210085255115490,-0.00215331724373312,0.00220724234473407,-0.00226270663336078,0.00231979440612000,-0.00237859597572831,0.00243920822495008,-0.00250173522256407,0.00256628890975622,-0.00263298986652147,0.00270196816917296,-0.00277336435186534,0.00284733048715952,-0.00292403140318963,0.00300364605802645,-0.00308636909545274,0.00317241261071561,-0.00326200816009132,0.00335540905447621,-0.00345289298497098,0.00355476503791943,-0.00366136116851319,0.00377305221645923,-0.00389024856503579,0.00401340556711620,-0.00414302988962330,0.00427968696305099,-0.00442400976734567,0.00457670924244743,-0.00473858668515236,0.00491054858898353,-0.00509362450782389,0.00528898868740642,-0.00549798642563195,0.00572216641338906,-0.00596332070106786,0.00622353447433531,-0.00650524856781341,0.00681133868908071,-0.00714521680725046,0.00751096229448811,-0.00791349353062965,0.00835879532603597,-0.00885422455900213,0.00940892731847729,-0.0100344180851776,0.0107453994685853,-0.0115609477328485,0.0125062698410704,-0.0136153815380233,0.0149353236672761,-0.0165330566304064,0.0185072526013980,-0.0210095898463344,0.0242858678072913,-0.0287624192110483,0.0352491360266123,-0.0454959873180899,0.0641146309484859,-0.108473164166835,0.351684970326287,0.283197416216450,-0.100941492036118,0.0614049295619216,-0.0441133854526662,0.0344124897425084,-0.0282020955314629,0.0238844584520012,-0.0207078799169934,0.0182721711568295,-0.0163446924812319,0.0147809757451865,-0.0134865678506610,0.0123971106796200,-0.0114672391594507,0.0106640562076046,-0.00996312474533430,0.00934591241228450,-0.00879810968700400,0.00830849189615460,-0.00786813040886261,0.00746983409514233,-0.00710774626629319,0.00677704884078020,-0.00647374186922948,0.00619447693465648,-0.00593642966986521,0.00569720108016410,-0.00547474035349108,0.00526728389030722,-0.00507330671151795,0.00489148340858597,-0.00472065651896548,0.00455981073020943,-0.00440805169677731,0.00426458853508774,-0.00412871927263410,0.00399981868546058,-0.00387732807881198,0.00376074665815159,-0.00364962420908401,0.00354355486026023,-0.00344217174682627,0.00334514242627582,-0.00325216492578479,0.00316296432180789,-0.00307728977014905,0.00299491191876919,-0.00291562064699242,0.00283922308404925,-0.00276554186749985,0.00269441360832369,-0.00262568753460797,0.00255922429004452,-0.00249489486700428,0.00243257965691781,-0.00237216760317625,0.00231355544386828,-0.00225664703342215,0.00220135273371645,-0.00214758886649634,0.00209527722000840,-0.00204434460367781,0.00199472244546489,-0.00194634642718757,0.00189915615369040,-0.00185309485225646,0.00180810909906510,-0.00176414856990486,0.00172116581264951,-0.00167911603931627,0.00163795693575912,-0.00159764848726405,0.00155815281851974,-0.00151943404658560,0.00148145814563968,-0.00144419282241021,0.00140760740131408,-0.00137167271842228,0.00133636102346487,-0.00130164588916329,0.00126750212725421,-0.00123390571062747,0.00120083370105150,-0.00116826418202476,0.00113617619632111,-0.00110454968784100,0.00107336544741835,-0.00104260506226635,0.00101225086876856,-0.000982285908351506,0.000952693886198312,-0.000923459132580123,0.000894566566605222,-0.000866001662201933,0.000837750416163094,-0.000809799318105260,0.000782135322187167,-0.000754745820460046,0.000727618617745353,-0.000700741907904703,0.000674104251408103,-0.000647694554116855,0.000621502047179641,-0.000595516267964076,0.000569727041951553,-0.000544124465524138,0.000518698889576035,-0.000493440903893135,0.000468341322243714,-0.000443391168122132,0.000418581661104787,-0.000393904203768593,0.000369350369123663,-0.000344911888528030,0.000320580640042490,-0.000296348637187224,0.000272208018067609,-0.000248151034839597};
double filter_weigth_broadside2[] = {0.000224170043480066,-0.000200257493833187,0.000176405919906360,-0.000152607930386222,0.000128856199352167,-0.000105143457159056,8.14624814664162e-05,-5.78060883898099e-05,3.41671237504768e-05,-1.05384544022979e-05,-1.30870403874661e-05,3.67164775251783e-05,-6.03569786685396e-05,8.40156788166693e-05,-0.000107699734934259,0.000131416334632208,-0.000155172704926278,0.000178976121097767,-0.000202833915679577,0.000226753487589997,-0.000250742311441119,0.000274807947043443,-0.000298958049136214,0.000323200377368413,-0.000347542806560110,0.000371993337274798,-0.000396560106729693,0.000421251400079261,-0.000446075662108197,0.000471041509368623,-0.000496157742795511,0.000521433360849894,-0.000546877573229336,0.000572499815187094,-0.000598309762518543,0.000624317347262434,-0.000650532774172883,0.000676966538026996,-0.000703629441831004,0.000730532615994157,-0.000757687538548430,0.000785106056500711,-0.000812800408391685,0.000840783248165931,-0.000869067670468763,0.000897667237456487,-0.000926596007257226,0.000955868564219231,-0.000985500051078060,0.00101550620320701,-0.00104590338511864,0.00107670862940469,-0.00110793967831970,0.00113961502822834,-0.00117175397716195,0.00120437667575228,-0.00123750418183329,0.00127115851903565,-0.00130536273973073,0.00134014099271356,-0.00137551859605104,0.00141152211557993,-0.00144817944957727,0.00148551992018454,-0.00152357437223552,0.00156237528020323,-0.00160195686406559,0.00164235521497592,-0.00168360843173199,0.00172575676914670,-0.00176884279956351,0.00181291158889434,-0.00185801088874566,0.00190419134637605,-0.00195150673445121,0.00200001420282941,-0.00204977455487481,0.00210085255115490,-0.00215331724373312,0.00220724234473408,-0.00226270663336078,0.00231979440611999,-0.00237859597572831,0.00243920822495008,-0.00250173522256407,0.00256628890975622,-0.00263298986652147,0.00270196816917296,-0.00277336435186534,0.00284733048715952,-0.00292403140318963,0.00300364605802645,-0.00308636909545273,0.00317241261071561,-0.00326200816009131,0.00335540905447621,-0.00345289298497098,0.00355476503791943,-0.00366136116851319,0.00377305221645923,-0.00389024856503579,0.00401340556711620,-0.00414302988962330,0.00427968696305099,-0.00442400976734566,0.00457670924244742,-0.00473858668515236,0.00491054858898353,-0.00509362450782389,0.00528898868740642,-0.00549798642563195,0.00572216641338906,-0.00596332070106785,0.00622353447433531,-0.00650524856781341,0.00681133868908071,-0.00714521680725046,0.00751096229448811,-0.00791349353062964,0.00835879532603598,-0.00885422455900213,0.00940892731847729,-0.0100344180851776,0.0107453994685853,-0.0115609477328485,0.0125062698410704,-0.0136153815380233,0.0149353236672761,-0.0165330566304064,0.0185072526013980,-0.0210095898463344,0.0242858678072913,-0.0287624192110483,0.0352491360266123,-0.0454959873180899,0.0641146309484859,-0.108473164166835,0.351684970326287,0.283197416216450,-0.100941492036118,0.0614049295619216,-0.0441133854526662,0.0344124897425084,-0.0282020955314629,0.0238844584520012,-0.0207078799169934,0.0182721711568295,-0.0163446924812319,0.0147809757451865,-0.0134865678506610,0.0123971106796200,-0.0114672391594507,0.0106640562076046,-0.00996312474533429,0.00934591241228450,-0.00879810968700400,0.00830849189615460,-0.00786813040886260,0.00746983409514233,-0.00710774626629319,0.00677704884078020,-0.00647374186922948,0.00619447693465649,-0.00593642966986521,0.00569720108016409,-0.00547474035349108,0.00526728389030722,-0.00507330671151795,0.00489148340858597,-0.00472065651896547,0.00455981073020943,-0.00440805169677731,0.00426458853508774,-0.00412871927263410,0.00399981868546058,-0.00387732807881197,0.00376074665815160,-0.00364962420908401,0.00354355486026022,-0.00344217174682627,0.00334514242627582,-0.00325216492578479,0.00316296432180788,-0.00307728977014905,0.00299491191876919,-0.00291562064699242,0.00283922308404925,-0.00276554186749985,0.00269441360832368,-0.00262568753460798,0.00255922429004451,-0.00249489486700428,0.00243257965691781,-0.00237216760317625,0.00231355544386828,-0.00225664703342214,0.00220135273371645,-0.00214758886649634,0.00209527722000840,-0.00204434460367781,0.00199472244546490,-0.00194634642718757,0.00189915615369040,-0.00185309485225645,0.00180810909906510,-0.00176414856990486,0.00172116581264950,-0.00167911603931627,0.00163795693575912,-0.00159764848726405,0.00155815281851973,-0.00151943404658560,0.00148145814563968,-0.00144419282241021,0.00140760740131408,-0.00137167271842228,0.00133636102346486,-0.00130164588916329,0.00126750212725422,-0.00123390571062747,0.00120083370105150,-0.00116826418202476,0.00113617619632112,-0.00110454968784100,0.00107336544741836,-0.00104260506226635,0.00101225086876855,-0.000982285908351501,0.000952693886198313,-0.000923459132580118,0.000894566566605225,-0.000866001662201938,0.000837750416163100,-0.000809799318105260,0.000782135322187166,-0.000754745820460046,0.000727618617745352,-0.000700741907904705,0.000674104251408105,-0.000647694554116861,0.000621502047179639,-0.000595516267964080,0.000569727041951555,-0.000544124465524141,0.000518698889576031,-0.000493440903893135,0.000468341322243719,-0.000443391168122136,0.000418581661104786,-0.000393904203768594,0.000369350369123657,-0.000344911888528032,0.000320580640042482,-0.000296348637187222,0.000272208018067607,-0.000248151034839598};
#endif //AUDIOTWOMICS_AUDIO_MAIN_H
