# OOP_Project-HEA_Login_System
OOP_Project-HEA_Login_System

# HEA Login System
조교가 개발한 첨단 HEA 시스템에 로그인 기능을 더하려고 한다. 로그인을 하기 위해선 이메일 주소와 비밀번호를 입력해야 한다. 해당 시스템은 이메일 주소와 비밀번호를 입력 받아 이메일 형식이 맞는지 확인하고 일정한 규칙에 의해 생성된 비밀번호와 일치하는지 확인하는 프로그램이다.

## 가정
모든 입력 값은 영문 소문자, 숫자, ‘@’, ‘.’만 입력 받는다고 가정
1. 이메일
- 입력 이메일의 최대 길이는 30이라고 가정
- 영문 소문자, 숫자, ‘@’, ‘.’로만 구성
2. 비밀번호
- 입력 비밀번호의 최대길이는 30 이라고 가정
- 영문 소문자, 숫자로만 구성

## 설명 및 실행 예시
컴퓨터가 사용자로부터 이메일과 비밀번호를 입력 받아 입력 값을 확인한 후, 입력 값에 따라 적절한 결과 문구가 출력된다. 프로그램은 입력 -> 검사 -> 결과 출력 3단계로 이루어진다. 먼저 유효한 이메일인지 체크하고 유효한 이메일이라면 아래 ‘비밀번호 생성규칙‘에 맞게 만들어진 비밀번호로 입력됐는지 확인한다.
1. 입력단계
- 사용자로부터 30자 이내의 이메일과 비밀번호를 입력 받는다. 프로그램을 실행하면, 사용자로부터 email을 입력 받기 위해 기다린다.
- 사용자가 email을 입력 후 엔터키를 누르면, 다음으로 password를 입력 받기 위해 기다린다.
2. 검사 및 출력 단계
- 사용자가 이메일과 비밀번호를 입력 후 엔터키를 누르면, 컴퓨터가 사용자로부터 입력 받은 이메일과 비밀번호를 검사한다.
- 모든 요건을 만족하는 경우, 로그인 성공 메시지를 출력 후 프로그램을 종료한다.
3. 재입력
- 사용자가 입력한 이메일 또는 패스워드가 틀린 경우, 적절한 에러메시지 출력 후 다시 시도하겠냐는 문구를 출력한다. 사용자가 y를 선택하면 다시 이메일과 비밀번호를 입력 받아 로그인을 시도한다. 사용자가 n을 선택하면 프로그램을 종료한다.

### 이메일 검사
입력 받은 이메일 문자열을 다음과 같이 3가지 조건에 따라 검사 후, 조건에 맞춰 에러 메시지를 출력한다.
1. 이메일 형식이 올바르지 않음: 이메일 모양을 띄고있지 않을 경우
2. 도메인 형식이 올바르지 않음: 주소 부분의 형식이 올바르지 않을 경우
3. 허용되지 않은 도메인: 주소 부분이 허용되지 않는 도메인일 경우
- 이메일 형식의 충족 조건은 ‘아이디@주소’이며, 주소의 조건은 naver(이름).com(최상위 도메인)과 같이 최소 하나 이상의 점(.)으로 이루어져야 하고 각 이름, 도메인들은 최소 1글자 이상이 되어야한다. 즉 hea9549@postech.ac.good.kr은 허용되지만, hea9549@.ac.kr, hea9549@postech...ac.kr, hea9549@postech.ac.은 허용되지 않는다.
- 주소는 ‘허용되는 도메인’에 속하는 이메일만 검사를 통과한다. 예를 들어, 허용되는 도메인이 ‘postech.ac.kr’ 일 경우 hea9549@postech.ac.kr 을 입력하면 통과, hea9549@daum.net 을 입력하면 검사를 통과하지 못한다. ‘허용되는 도메인’은 파일로 주어지며 5쪽을 참고하여 구현한다. 주어진 파일에 없는 도메인인 경우 검사를 통과하지 못한다.

#### 허용되는 도메인
허용되는 도메인을 검사할 때, 파일 allowed_domain.txt 에 있는 도메인인지 검사를 하게 된다.
- 데이터들은 도메인 주소이며 줄(line)단위로 구분된다.
- 도메인 최대 개수는 20개를 넘지 않으며, 도메인 주소의 길이는 20을 넘지 않는다. (단, 도메인 최대 개수와 주소 길이 부분은 구현 방법에 따라 사용하지 않을 수도 있다.)
- 이와 같이 구성된 어떤 파일에 대해서도 처리할 수 있도록 구현해야 한다. 단, 도메인 주소 형식이 틀리거나 파일 구성에 대한 에러는 고려할 필요가 없다.

### 비밀번호 검사
이메일 검사를 통과 한 경우, 입력된 비밀번호가 아래 ‘비밀번호 생성 규칙’에 맞게 생성된 비밀번호와 일치하는지 확인한다.

#### 비밀번호 생성 규칙
비밀번호는 입력한 사용자의 이메일 주소를 이용해 생성한다. 이메일 주소는 크게 아이디 부분과 도메인 부분으로 나눌 수. 있다.
( 예: hea9549(아이디)@postech.ac.kr(도메인) )
이때, 아이디 부분과 도메인 부분을 번갈아 가면서 한 글자씩 이용해 10자의 비밀번호를 만든다. 즉 hea9549@postech.ac.kr 의 이메일 경우 비밀번호는 hpeoas9t5e 이다.
만약 아이디와 도메인 합이 10글자가 넘지 않을 경우 부족한 공간은 0으로 채운다. 만약 아이디 또는 이메일 한쪽이 짧을 경우 나머지 공간은 아이디 또는 이메일로 나머지를 채운다.

( 예: a@postech.ac.kr -> apostech.a )
( 예: a@b.c -> ab.c000000 )
