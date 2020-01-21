#!/usr/bin/env python

"""
Implements the Poseidon permutation:
Starkad and Poseidon: New Hash Functions for Zero Knowledge Proof Systems
 - Lorenzo Grassi, Daniel Kales, Dmitry Khovratovich, Arnab Roy, Christian Rechberger, and Markus Schofnegger
 - https://eprint.iacr.org/2019/458.pdf
Other implementations:
 - https://github.com/shamatar/PoseidonTree/
 - https://github.com/iden3/circomlib/blob/master/src/poseidon.js
 - https://github.com/dusk-network/poseidon252
"""

from collections import namedtuple
from poseidon_params import mds, round_constants

p = 0x1C4C62D92C41110229022EEE2CDADB7F997505B8FAFED5EB7E8F96C97D87307FDB925E8A0ED8D99D124D9A15AF79DB26C5C28C859A99B3EEBCA9429212636B9DFF97634993AA4D6C381BC3F0057974EA099170FA13A4FD90776E240000001

_PoseidonParams = namedtuple('_PoseidonParams', ('p', 't', 'nRoundsF', 'nRoundsP', 'e', 'constants_C', 'constants_M'))
DefaultParams = _PoseidonParams(p, 3, 8, 33, 11, round_constants, mds)

def poseidon_mix(state, M, p):
    return [ sum([M[i][j] * x for j, x in enumerate(state)]) % p
             for i in range(len(M)) ]

def poseidon(inputs, params=None, state=None):
    if params is None:
        params = DefaultParams
    assert isinstance(params, _PoseidonParams)
    assert len(inputs) > 0 and len(inputs) < params.t
    if state is None:
        state = [0] * params.t
    else:
        assert len(state) == params.t

    for i in range(len(inputs)):
        state[i] = inputs[i] + state[i]

    # half full rounds
    half = params.nRoundsF//2
    for i in range(half):
        for j in range(params.t):
            state[j] = state[j] + params.constants_C[i][j]          # ARK
        state = [pow(x, params.e, params.p) for x in state]         # x**a
        state = poseidon_mix(state, params.constants_M, params.p)   # MDS

    # partial rounds
    offset = params.nRoundsF//2
    for i in range(params.nRoundsP):
        for j in range(params.t):
            state[j] = state[j] + params.constants_C[i + offset][j] # ARK
        state[0] = pow(state[0], params.e, params.p)                # x[0]**a
        state = poseidon_mix(state, params.constants_M, params.p)   # MDS

    # half full rounds
    offset = params.nRoundsP + params.nRoundsF//2
    for i in range(params.nRoundsF//2):
        for j in range(params.t):
            state[j] = state[j] + params.constants_C[i + offset][j] # ARK
        state = [pow(x, params.e, params.p) for x in state]         # x**a
        state = poseidon_mix(state, params.constants_M, params.p)   # MDS
    return state[0]

if __name__ == "__main__":
    msgs = [[240717916736854602989207148466022993262069182275],
       [240717916736856083605108215037963941411481087821],
       [240717916736854598292360696510787486996073117253],
       [0]]
    state = [[11755705189390821252061646515347634803721008034042221776076198442214047097736416191977544342102890624152325311676405596068127350375523649920335519154711182264164630561278473895587364446094244598242170557714936573775626048265230,
    27515311459815300529244367822740863112445008780714100624704075938494921938258491804705259071021760016622352448625351667277308772230882264292787686108079884001293592223592113739068864847707009580257641842924278675467231562803771,
    2396632434414439310737449031743778257385962871664374090342438175577792963806884089307026050137579268946498687720760431246070701978535951122430182545476853420233411791434797499475546364343179083506203526451182750041179531584522],
    [24341961192682957976528713867896718267802514525608179163038431088957380255238148947966553318475122486385689169865843674688259772170774897200006501044592562775146371270239803213089333281332791538737728339660194402901356418462758,
    18224768784793472193818342531974732507375802141911175730510427250745989717476712789732404502097870291611504005148052926307457425647585391582745622535456140698710270052661633861945779806393216494112206150363378559461764675150019,
    24275567241967455066895987376195669675464660419387611943726566148619049658147070921069671853559534046019384462399261519316012965282655704040635022637030885350053672338475287674944526907726691136522014116807515847622063524729215],
    [10750110435767046983454045187671099514739733034566671521925896662668294860264709060384236385295463432545325451980016479659913827658594515079120134623071305934006485197771950662022752967275205776146414789256179852832585246277135,
    8904455874005639433592278235532509199702939465001270112155953999636926342280273055763340728158647285485979535981075100188059611800277960438095719726511925245756237924437620016602630288663342596748711971774951187120855819006254,
    32530237352315271838115261734720283499544522470073175811970824147732315975479559777637890800660222426763032867915025114471287205710769908680232969801493216312164238036604377671062479707846578922656464522981144652357387637752612],
    [34862842728213847749764780789494678728670423208602929571896961056573803098074132905304873030635377933739117043619468734830991448221869197939483134103171107112118584937110067067547102424492071823030360093209596106303243891804197,
    17081227013397223905512048865245015172588387142622756033708188882141875904207452273551785481563105856198959587137267960219725430124795159846635170869198394793534706044519183438281433645289205371329733705735120518132198922596081,
    38222598208661293154358098467913225947501468879718283947325552423417581445633039988767989340378891826663231756617039996089956309806010436055674976914944611798818889926367328052912099929296285277861067843021509088943796472188515]]
    state_salted = [[12533643450054795756823453029365504553515591994982683067778743757731045656901877838390337307432606597605722929181003541883698280404037532188130792469984007830776655884749273619568748977588850633002842891824421144254205480650889, 11424051011783589020728033858207338360115011586319105486577164679369541827036622718261152612356933051847665060399342577606687138634514909137322464405009046776122289218219635711928546448596632820987352314394079320288122465748911, 39185347011283210905613202078897096638587481176104209365808549315897855094947085813036056946095764665516212523543914697639182969832321597339424089322107344317364238215650016974636289183243572136439307178222037664811386761045632],
            [41134496029073949877571442653384037976779277341149147121461998219122889011087880847132157108196812993722255907209627151254668766683801850320306643952970781475148168823684911896946254346731110056155784103629225590338564120354238, 30083191028810731583856077671086662508834006120959537118544664223910007538839371339742789694817222440938616800227086626039641064820124865234112719084099303118097357841237486664984957165339208249602261403216922266233474776979177, 30941503080447168602544579623004311571393886573146926957531843826897461869372645190120210303676063390167333708689817980693766327970657339131526020362261482995294600116655196580295831670257494983373798815386494520182347593418519],
            [3000651317718928996965764444877829720937059283866220452301047354685178304906142868240711179165094602994376893682711333455154088438857812791745031344718110025073244469028497125056135733068640680069083176440555528068283694396430, 3790674861851267856980186906883282032270966151574038376830892067671410011830012586757581400213492107739943660871512025123005870466657748977452924590304983171412142610793562674345324969724127944674203615177502414336409089626634, 1656634427787501392778457067186618907735175994297063844146652231444116658072335816754169864424929519583957755071746145423710867356166232517661481434981536100932841425863861378888630215802107378760005008459161751187508368814532],
            [14082601331018967252857547467482961810155464041864176028024081113016921356729192011802932226764586078404381875372002999911860076674471688109281240678646733110785400544410878078577906037372809678100937040028710290560506961560609, 5040045206231025602461879193748953413316059215206740608698438969216948001753779566716212983696172928265312533138903849598411403094196600146405831055123438610535343664595336421562467883561759225504063893993929362759485649599351, 359146613821575154272085530325112582940647646519666677391143428805933969794173385976075511169125532030294411220266412095251780538051653388808083629859743895355383979907020054213654038990232065183252704915867119307643266439726]]

    for i in range(len(msgs)):
        assert poseidon(msgs[i]) == state[i][0]
        # print("unsalted" + " : " + str(hex(msgs[i][0])) + " : " + str(hex(state[i][0])))
        assert poseidon(msgs[i], state=state[0]) == state_salted[i][0]
        # print("salted" + " : " + str(hex(msgs[i][0])) + " : " + str(hex(state_salted[i][0])))
