# Documentação IoTDoc - Módulo 4 - Inteli

**_Os trechos em itálico servem apenas como guia para o preenchimento da seção. Por esse motivo, não devem fazer parte da documentação final_**

## Nome do Grupo

#### Nomes dos integrantes do grupo

<img src="../assets/inteli.png">

## Sumário

[1. Introdução](#c1)

[2. Metodologia](#c2)

[3. Desenvolvimento e Resultados](#c3)

[4. Conclusões e Recomendações](#c4)

[5. Referências](#c5)

<br>


# <a name="c1"></a>1. Introdução (sprint 1)

## Parceiro de Negócio: Renault do Brasil

### Perfil da Empresa

&nbsp;&nbsp;&nbsp;&nbsp;A Renault do Brasil é uma subsidiária da Renault S.A., uma das maiores montadoras de automóveis do mundo, com sede na França. A empresa atua no Brasil desde 1998 e é reconhecida por sua inovação tecnológica, qualidade de produtos e compromisso com a sustentabilidade. A Renault do Brasil oferece uma ampla gama de veículos, incluindo carros compactos, SUVs e veículos elétricos, atendendo a diversos segmentos do mercado automotivo nacional e internacional. 

&nbsp;&nbsp;&nbsp;&nbsp;Localizada em São José dos Pinhais, Paraná, a fábrica da Renault no Brasil é uma das mais modernas do país, equipada com tecnologias avançadas de produção e sustentabilidade ambiental. O porte da empresa é de grande escala, empregando milhares de colaboradores e contribuindo significativamente para a economia local e nacional.


### Problema a Ser Resolvido

**Contexto do Desafio**
A Renault enfrenta um desafio técnico relacionado às análises de Squeak and Rattle (ruídos e vibrações indesejados em veículos).

**Limitação Atual:**
As análises do tipo "e-line" (método de simulação) dependem de sinais de entrada precisos que representem deslocamento x tempo ou força x tempo. Atualmente, não existe uma base de dados estruturada que contemple as diferentes excitações que os veículos sofrem em diversos tipos de pistas.

**Impacto:**
Sem dados reais e padronizados sobre o comportamento dos veículos em diferentes condições de rodagem, as simulações perdem precisão, dificultando a previsão e mitigação de problemas de Squeak and Rattle durante o desenvolvimento de novos projetos.

**Necessidade:**
Estudar sistematicamente os tipos de pistas e coletar dados experimentais que possam alimentar as simulações com sinais de entrada genéricos e representativos da realidade operacional dos veículos.

## 1.1 Objetivos

1.1.1 Objetivos Gerais

&nbsp;&nbsp;&nbsp;&nbsp;A Renault do Brasil, reconhecida por sua inovação e compromisso com a mobilidade sustentável, busca constantemente aprimorar seus processos de engenharia e qualidade. Dentro dessa visão, o projeto tem como objetivo geral desenvolver uma solução IoT capaz de coletar e armazenar dados de aceleração e força em veículos de teste, criando uma base de dados padronizada que apoie simulações de Squeak and Rattle (ruídos e vibrações estruturais).

&nbsp;&nbsp;&nbsp;&nbsp;Com isso, pretende-se tornar o processo de análise mais preciso e automatizado, reduzindo a necessidade de testes físicos e contribuindo para práticas de desenvolvimento mais eficientes e sustentáveis. O projeto também busca aproximar a universidade do ambiente industrial, permitindo a aplicação prática de tecnologias emergentes e fortalecendo a parceria entre o Inteli e a Renault.

1.1.2 Objetivos Específicos com o Projeto

- Criar um sistema IoT funcional: Desenvolver um protótipo embarcado que use sensores de aceleração e força conectados a um microcontrolador,  para coletar dados durante os testes do veículo.

- Coletar e enviar dados em tempo real: Permitir que os sinais obtidos pelos sensores sejam transmitidos automaticamente para uma plataforma digital por meio de conexão sem fio, como Wi-Fi ou Bluetooth.

- Construir um banco de dados de perfis de pista: Organizar e armazenar os dados coletados, formando uma base que represente diferentes tipos de pista, velocidades e condições de rodagem.

- Apoiar análises de Squeak and Rattle: Disponibilizar informações úteis para estudos e simulações que busquem compreender e reduzir ruídos e vibrações estruturais nos veículos da Renault.

- Assegurar a confiabilidade das medições: Documentar e padronizar todo o processo de coleta, transmissão e tratamento dos dados, garantindo a qualidade dos resultados obtidos.


## 1.2 Proposta da solução

&nbsp;&nbsp;&nbsp;&nbsp;A solução proposta para o projeto envolve o desenvolvimento de um dispositivo IoT (Internet das Coisas) capaz de monitorar as condições de Squeak and Rattle por meio de sensores instalados nos veículos e envio de dados por lotes. Esse dispositivo será equipado com dois sensores principais (Acelerometros e Piezoeletricos) para a captação de dados relevantes, como aceleração, vibração, velocidade e outros indicadores relevantes para a melhor interpretabilidade dos dados para os simuladores de Squeak and Rattle.

&nbsp;&nbsp;&nbsp;&nbsp;Os dados captados pelos sensores serão enviados periodicamente para a nuvem e armazenados em um banco de dados relacional, garantindo um fluxo contínuo e seguro de informações.

&nbsp;&nbsp;&nbsp;&nbsp;Além disso, a solução inclui o desenvolvimento de uma interface de controle intuitiva que permitirá a definir variáveis importantes que devem ser consideradas no envio desses dados para o banco de dados. Tais variáveis podem incluir o tipo de pista, condições climáticas, velocidade do veículo, entre outros fatores que possam influenciar os resultados das análises de Squeak and Rattle.

## 1.3 Justificativa

&nbsp;&nbsp;&nbsp;&nbsp;A solução proposta busca suprir a falta de dados padronizados sobre vibrações e ruídos em veículos, essenciais para análises precisas de Squeak and Rattle. O uso de um dispositivo IoT com sensores acelerômetros e piezoelétricos permite coletar e enviar dados reais de forma automatizada e segura, criando uma base confiável para futuras simulações.

&nbsp;&nbsp;&nbsp;&nbsp;O envio das informações para a nuvem e seu armazenamento em um banco de dados relacional garantem melhor organização e acesso aos dados, enquanto a interface de controle intuitiva torna o sistema adaptável a diferentes condições de teste. Seus benefícios incluem a redução do tempo e custo dos testes, além de aumentar a precisão das análises, contribuindo para a melhoria contínua dos processos de engenharia da Renault.

&nbsp;&nbsp;&nbsp;&nbsp;A solução se diferencia por sua capacidade de integrar hardware, conectividade e análise de dados em uma única plataforma, facilitando a coleta e interpretação das informações. Isso não apenas melhora a eficiência dos testes, mas também contribui para a inovação nos processos de engenharia da Renault, alinhando-se com as tendências atuais de digitalização e automação na indústria automotiva.

# <a name="c2"></a>2. Metodologia (sprint 3)

_Descreva as etapas da metodologia RM-ODP que foram utilizadas para o desenvolvimento, citando o referencial teórico. Você deve apenas enunciar os métodos, sem dizer ainda como ele foi aplicado e quais resultados obtidos._

# <a name="c3"></a>3. Desenvolvimento e Resultados 

## 3.1. Domínio de Fundamentos de Negócio

_Link para os templates de negócios: https://drive.google.com/drive/folders/1lTqisJ_gxxtc5J5aXM8ula2kQ4MsII_M?usp=sharing_

### 3.1.1. Contexto da Indústria (sprint 1)	

_O aluno deve fornecer informações sobre a concorrência (mínimo 3 competidores - 1 parágrafo; modelo de negócio - 1 parágrafo, e tendências - 1 parágrafo). Considere o setor do parceiro. Por exemplo, se o parceiro for a Rede Gazeta, o setor de Televisão.<br>
<br>
A análise de 5 forças deve ser feita considerando também o parceiro, o aluno deve preencher o template disponibilizado. No link a seguir há indicações de como avaliar as 5 forças: https://rockcontent.com/br/blog/5-forcas-de-porter/_

### 3.1.2. Análise SWOT (sprint 1)	
 

&nbsp;&nbsp;&nbsp;&nbsp; Segundo Kevin Dunne, a análise SWOT (Strengths, Weaknesses, Opportunities e Threats) é uma ferramenta estratégica utilizada para avaliar a situação atual de uma organização, identificando seus pontos fortes e fracos, assim como as oportunidades e ameaças do ambiente externo. Essa análise possibilita a construção de estratégias mais eficazes, alinhadas aos objetivos da instituição, e contribui para aumentar as chances de sucesso dos projetos.

&nbsp;&nbsp;&nbsp;&nbsp;A aplicação da análise SWOT permite compreender de forma ampla o cenário em que a organização está inserida, nesse caso a Renault Brasil, fornecendo embasamento para decisões mais assertivas. Ao explorar as forças, corrigir as fraquezas, aproveitar as oportunidades e se preparar para as ameaças, é possível garantir um direcionamento mais consistente no andamento do projeto.

### 3.1.2.1  Visualização da análise SWOT:

<div align="center">
Figura 4 - Análise SWOT
<img src="../document/analiseSWOT.png"
<sup>Fonte: Material alterado pelos autores com base no tamplete disponível em: https://uolhost.uol.com.br/blog/matriz-swot-conheca-melhor-seu-negocio-e-otimize-suas-estrategias/</sup>
</div>
 

### 3.1.2.2 Forças (Internas):

### Liderança em veículos acessíveis e elétricos
&nbsp;&nbsp;&nbsp;&nbsp; A Renault Brasil destaca-se com o Kwid como o carro mais barato do país e o Kwid E-Tech como veículo elétrico acessível, com IPI zerado, impulsionando vendas em segmentos econômicos e sustentáveis. Isso mitiga fraquezas de custos ao atrair volume de vendas e explora oportunidades de incentivos fiscais, reduzindo impactos de ameaças econômicas.

### Prêmios e reconhecimento local
&nbsp;&nbsp;&nbsp;&nbsp; Modelos como Kardian (Carro do Ano 2025) e Megane E-Tech (Compra do Ano) reforçam qualidade e inovação, com tecnologia OpenR Link integrada. Relaciona-se com fraquezas ao melhorar reputação apesar de recalls, e conecta a oportunidades de mercado, combatendo ameaças de concorrentes.

### Crescimento de vendas no primeiro semestre de 2025
&nbsp;&nbsp;&nbsp;&nbsp; Vendas subiram 8,8% para 60,7 mil unidades no primeiro semestre, tornando o Brasil o 7º mercado global do grupo. Essa força explora oportunidades de expansão veículos elétricos, compensa fraquezas operacionais e resiste a ameaças instáveis via diversificação local.

### 3.1.2.3 Fraquezas (Internas):


### Dependência de cadeia de suprimentos global
&nbsp;&nbsp;&nbsp;&nbsp; Vulnerável a variações cambiais e interrupções, afetando produção local de veículos elétricos e aumentando custos. Agrava ameaças econômicas, enfraquece forças de crescimento, mas oportunidades de incentivos fiscais podem ajudar a reduzir impactos.

### Pressão de custos em inovação
&nbsp;&nbsp;&nbsp;&nbsp; Altos investimentos em tech como E-Tech e OpenR Link pressionam margens, especialmente em um mercado sensível a preços. Limita forças de prêmios, é piorada por ameaças regulatórias, mas interliga a oportunidades de expansão para diluir custos via volume.

### Market share limitado em premium
&nbsp;&nbsp;&nbsp;&nbsp; Foco em econômicos como Kwid restringe penetração em SUVs premium, com recalls recentes afetando confiança. Enfraquece forças de vendas, amplifica ameaças de concorrentes chineses, mas oportunidades de veículos elétricos podem expandir para novos segmentos.

### 3.1.2.4 Oportunidades (Externas):

### Expansão híbridos/EVs no Brasil
&nbsp;&nbsp;&nbsp;&nbsp; Mercado de EVs no Brasil cresce 58% em julho 2025. Parceria com Geely lança EX5 elétrico em julho, usando rede Renault. Kwid E-Tech impulsiona vendas 8,8% no H1.

### Alianças Nissan-Mitsubishi para tech
&nbsp;&nbsp;&nbsp;&nbsp; Aliança Renault-Nissan-Mitsubishi avança em EVs. Compartilham plataformas como CMF-B para Micra EV e Eclipse Cross. Em setembro 2025, projetos conjuntos na fábrica Ampere Douai melhoram EVs e autonomia.

### Aumento concessionárias regionais (Brasil)
&nbsp;&nbsp;&nbsp;&nbsp; No Brasil, 23 novas lojas Geely via Renault em 19 cidades, totalizando 105. Aumenta vendas de EVs. Mercado brasileiro tem 1,8mi unidades até agosto 2025, com Renault crescendo.

### 3.1.2.5 Ameaças (Externas):

### Concorrência de marcas chinesas
&nbsp;&nbsp;&nbsp;&nbsp; Marcas como BYD dominam veículos elétricos com preços agressivos, pressionando market share da Renault Brasil. Enfraquece forças de liderança, piora fraquezas de dependência e reduz oportunidades de expansão.

### Instabilidade econômica no Brasil
&nbsp;&nbsp;&nbsp;&nbsp; Flutuações e pressões comerciais afetam demanda e custos operacionais locais. Desafia forças de vendas, amplifica fraquezas de inovação e ameaça oportunidades de incentivos se políticas mudarem.

### Regulamentações ambientais rigorosas
&nbsp;&nbsp;&nbsp;&nbsp; Normas mais rígidas para emissões exigem adaptações caras em veículos elétricos e produção local. Limita forças de sustentabilidade, agrava fraquezas de custos e impacta oportunidades de mercado se não cumpridas.

### 3.1.2.6 Conclusão: 

&nbsp;&nbsp;&nbsp;&nbsp; A Renault Brasil apresenta um posicionamento sólido no mercado automotivo local, impulsionado por forças internas como a liderança em veículos acessíveis e elétricos, prêmios de reconhecimento e crescimento de vendas de 8,8% no primeiro semestre de 2025. No entanto, fraquezas como a dependência de suprimentos globais, pressão de custos em inovação e market share limitado em segmentos premium demandam atenção para evitar vulnerabilidades.
Em resumo, a Renault Brasil está bem posicionada para crescer na transição para mobilidade elétrica, desde que invista em autonomia operacional e inovação estratégica para equilibrar riscos e capitalizar tendências sustentáveis, visando liderança duradoura no setor.

### 3.1.3. Descrição da Solução a ser Desenvolvida (sprint 1)	

#### 3.1.3.1 Qual é o problema a ser resolvido

#### 3.1.3.2 Qual a solução proposta (visão de negócios)

#### 3.1.3.3 Como a solução proposta deverá ser utilizada

#### 3.1.3.4 Quais os benefícios trazidos pela solução proposta

#### 3.1.3.5 Qual será o critério de sucesso e qual medida será utilizada para o avaliar
	
### 3.1.4. Value Proposition Canvas (sprint 1)	

_O Canvas da proposta de valor deve ser feito considerando a solução que vocês estão desenvolvendo. Usar o template disponível no drive da turma._     

### 3.1.5. Matriz de Riscos (sprint 1)	

_A Matriz de Risco deve ser desenhada considerando o projeto que os alunos estão criando. Deve ser entregue no template disponível no drive da turma. Os alunos devem enumerar os riscos, distribuí-los na matriz e justificar suas decisões._     

### 3.1.6. Política de Privacidade de acordo com a LGPD (sprint 1)	

_A Política de privacidade para o projeto de acordo com a LGPD deve ser escrita considerando o projeto que os alunos estão criando. Os pontos a seguir precisam ser apresentados. O aluno pode utilizar  o Gerador de Política de Privacidade (https://www.nuvemshop.com.br/ferramentas/gerador-politica-de-privacidade), criado pela Nuvemshop e, de acordo com a empresa, já adaptado a LGPD para ter uma prévia e ajustar de acordo com o seu projeto._

#### 3.1.6.1 Informações gerais sobre a empresa / organização

#### 3.1.6.2 Informações sobre o tratamento de dados

#### 3.1.6.3 Quais são os dados coletados

#### 3.1.6.4 Onde os dados são coletados 

#### 3.1.6.5 Para quais finalidades os dados serão utilizadas

#### 3.1.6.6 Onde os dados ficam armazenados 

#### 3.1.6.7 Qual o período de armazenamento dos dados (retenção)

#### 3.1.6.8 Uso de cookies e/ou tecnologias semelhantes

#### 3.1.6.9 Com quem esses dados são compartilhados (parceiros, fornecedores, subcontratados)

#### 3.1.6.10 Informações sobre medidas de segurança adotadas pela empresa

#### 3.1.6.11 Orientações sobre como a empresa/organização atende aos direitos dos usuários

#### 3.1.6.12 Informações sobre como o titular de dados pode solicitar e exercer os seus direitos

#### 3.1.6.13 Informações de contato do Data Protection Officer (DPO) ou encarregado de proteção de dados da organização


### 3.1.7. Bill of Material (BOM) (sprint 1)
_BOM (Bill of Material) pode ser definido como uma lista completa de materiais, que detalha todos os itens necessários para construir, fabricar ou reparar um produto. Deve-se preencher o template fornecido.




## 3.2. Domínio de Fundamentos de Experiência de Usuário 

### 3.2.1. Personas (sprint 1)	

&nbsp;&nbsp;&nbsp;&nbsp;Segundo Louise Bruton (2022), personas no contexto de UI/UX, são representações fictícias de usuários reais, criadas com base em pesquisas qualitativas e quantitativas para auxiliar designers a compreenderem melhor o público-alvo e tomarem decisões de design mais informadas. Essas personas incluem detalhes demográficos, comportamentais, motivações, dores e objetivos, promovendo empatia e garantindo que o produto priorize as necessidades dos usuários, o que resulta em experiências mais intuitivas e eficazes.

&nbsp;&nbsp;&nbsp;&nbsp;Tendo em vista esses pontos, em nosso projeto nós criamos duas personas: um sendo o piloto que conduzirá o carro em tetes de Squeak and Rattle e o outro sendo o engenheiro de simulação da Renault, que analisará o resultados e relatórios para tirar conclusões úteis. Fizemos isso para auxiliar o desenvolvimento do projeto e não perdermos de vista os nossos objetivos.


**João Silva, Piloto de Teste**

<img src="../assets/persona-1.png" alt="Persona 1" />

&nbsp;&nbsp;&nbsp;&nbsp;João Silva representa o usuário operacional que interage diretamente com o dispositivo IoT durante os testes em pistas. Como piloto experiente, ele será responsável por instalar o dispositivo, ativar o sistema embarcado e conduzir o veículo em condições reais de rodagem, coletando dados de aceleração (A x t) e força (F x t).

**Por que a persona João Silva?**

&nbsp;&nbsp;&nbsp;&nbsp;Entender as dores de João, como configurações complexas que demandam tempo ou interferem na condução, permite projetar interfaces simples e intuitivas. Isso reduz riscos, como distrações durante a direção, alinhando-se ao objetivo de coletar dados de forma automatizada e confiável.

&nbsp;&nbsp;&nbsp;&nbsp;Personas como essa promovem empatia para experiências diferentes das dos desenvolvedores, ajudando a priorizar requisitos como conectividade Wi-Fi/Bluetooth robusta e feedback imediato sobre a qualidade das medições. No MVP do projeto, isso assegura que o hardware seja prático, evitando falhas que invalidem rodagens inteiras e contribuindo para a viabilidade técnica da solução IoT.

<br/>

**Maria Oliveira, Engenheira de Simulação**

<img src="../assets/persona-2.png" alt="Persona 2" />

&nbsp;&nbsp;&nbsp;&nbsp;Maria Oliveira personifica o usuário analítico que processa os dados coletados, utilizando-os para simulações CAE (Computer-Aided Engineering) de Squeak and Rattle. Como engenheira sênior, ela acessa a plataforma as a service, analisa sinais para gerar indicadores de criticidade e espectros de frequência, e integra os dados em modelos virtuais.

**Por que a persona Maria Oliveira?**

&nbsp;&nbsp;&nbsp;&nbsp;As frustrações de Maria, como a falta de dados confiáveis e coletivamente exaustivos de diferentes cenários de rodagem reais e de diferentes veículos, necessários para alavancar a qualidade de análises Squeak and Rattle, destacam a necessidade de padronização e armazenamento contínuo. Isso apoia o objetivo do projeto de criar um sinal de entrada genérico para avaliações "e-line", permitindo análises comparativas e previsões precisas.

&nbsp;&nbsp;&nbsp;&nbsp;Ao entender motivações como avançar na precisão das simulações para veículos mais duráveis, a persona alinha o design com necessidades de integração com softwares existentes, como brokers MQTT.

**Conclusão**

&nbsp;&nbsp;&nbsp;&nbsp;As personas João Silva e Maria Oliveira são fundamentais para um design centrado no usuário, construindo empatia e prevendo interações em um projeto IoT complexo. Elas garantem que o protótipo atenda às demandas operacionais e analíticas, alinhando-se aos objetivos da Renault de automação, precisão e sustentabilidade. Ao incorporar essas representações, o projeto não só resolve problemas práticos, como aquisição de dados em pistas variadas, mas também pavimenta o caminho para expansões com IA e simulações digitais.


### 3.2.2. Jornada do Usuário e Storyboard (sprint 2)	

_Coloque aqui seu Mapa de Jornada do Usuário:_
- _Ferramenta visual da sequência de interações do usuário._
- _Retrata sentimentos, obstáculos e satisfação ao longo de um processo._
- _Identifica oportunidades de melhoria na experiência._
- _Fazer pelo menos um mapa de jornada do usuário_

_Coloque aqui seu Storyboard:_
- _Ilustração sequencial da interação do usuário com a solução._
- _Enfatiza fluxo, interações e narrativa visual._
- _Destaca pontos de atrito ou oportunidades na experiência._
- _Criar ao menos um storyboard._

## 3.3. Solução Técnica	

 &nbsp;&nbsp;&nbsp;&nbsp;Nesta subseção, são feitos os detalhamentos em relação às especificações e capacidades téncicas do dispositivo IOT, delimitando-se seus requisitos funcionais e não funcionais, seu planejamento de arquitetura e demais características estruturais.

### 3.3.1. Requisitos Funcionais (sprint 1)	

 &nbsp;&nbsp;&nbsp;&nbsp;De acordo com Wiegers (2013) e Kotonya e Sommerville (1998), a Engenharia de Requisitos envolve a identificação e documentação de funcionalidades e constraints que um sistema deve satisfazer, capturando as demandas e perspectivas dos envolvidos no projeto. Esses requisitos classificam-se em funcionais, que definem as operações e comportamentos específicos que o software ou hardware precisa executar, e não funcionais, que estabelecem critérios de qualidade, como eficiência, interface, proteção de dados e acessibilidade. Os requisitos representam elementos fundamentais no ciclo de vida de produtos tecnológicos e exigem uma avaliação rigorosa, equilibrando as expectativas dos usuários com as viabilidades técnicas, visando a criação de soluções robustas, seguras e otimizadas.

 &nbsp;&nbsp;&nbsp;&nbsp;A seguir será detalhado os requisitos funcionais do projeto, seguindo a visão de funcionalidades, alinhados às demandas e problemas de negócios do parceiro Renault.

| **RF#** | **Descrição** | **Regra de negócio** | 
|----------|----------|----------|
|RF01|O sistema deve adquirir dados de aceleração (A x t) a partir de acelerômetros instalados no veículo durante ensaios em diferentes perfis de pista.|A aquisição de dados de aceleração deve ocorrer apenas durante a execução de testes veiculares padronizados, garantindo que os dados sejam coletados em condições controladas de rodagem para análises de Squeak and Rattle.|
|RF02|O sistema deve adquirir dados de força (F x t) a partir de sensores piezoelétricos instalados no veículo durante ensaios em diferentes perfis de pista.|A aquisição de dados de força deve ocorrer apenas durante a execução de testes veiculares padronizados, garantindo que os dados sejam coletados em condições controladas de rodagem para análises de Squeak and Rattle.|
|RF03|O sistema deve formatar os dados coletados (aceleração e força) em estruturas compatíveis com o protocolo MQTT, incluindo timestamps e identificadores de sensor.|Os dados formatados devem incluir metadados como perfil de pista, velocidade e identificador do teste, para permitir a rastreabilidade e correlação com condições específicas de rodagem veicular.|
|RF04|O sistema deve estabelecer uma conexão Wi-Fi com uma rede disponível para transmissão de dados.|A conexão Wi-Fi deve ser iniciada automaticamente ao ligar o dispositivo embarcado, priorizando redes pré-configuradas para ambientes de teste veicular na Renault ou proximidades do campus Inteli.|
|RF05|O sistema deve transmitir os dados formatados via protocolo MQTT para uma plataforma as a service configurada como endpoint.|A transmissão via MQTT deve ocorrer em tempo real durante os testes, utilizando tópicos específicos para separar dados de aceleração e força, garantindo a entrega para análises posteriores em projetos Renault.|
|RF06|O sistema deve permitir a definição de chaves de identificação de usuário (como API keys ou credenciais) para acesso seguro à plataforma de dashboard.|As chaves de identificação devem ser associadas a perfis de engenheiros da Renault ou equipe acadêmica, limitando o acesso apenas a stakeholders autorizados envolvidos no projeto de Squeak and Rattle.|
|RF07|O sistema deve permitir a definição e registro de devices (dispositivos IoT) dentro da plataforma as a service.|Cada device registrado deve ser vinculado a um veículo ou configuração de teste específica, permitindo o gerenciamento de múltiplos protótipos em diferentes pistas de rodagem.|
|RF08|O sistema deve armazenar os dados recebidos via MQTT em uma estrutura básica de banco de dados na plataforma as a service.|O armazenamento deve organizar os dados por teste, incluindo filtros por perfil de pista e velocidade, para facilitar a geração de bases de dados consistentes para simulações futuras de Squeak and Rattle.|
|RF09|O sistema deve fornecer representação gráfica dos dados coletados, incluindo gráficos de aceleração e força ao longo do tempo, no dashboard da plataforma.|As representações gráficas devem permitir visualização comparativa entre diferentes perfis de pista e velocidades, apoiando análises de criticidade e padrões de resposta veicular associados a ruídos de Squeak and Rattle.|
|RF10|O sistema deve permitir a exportação de dados armazenados em formatos como CSV ou JSON para análises externas.|A exportação deve ser restrita a usuários autenticados e deve incluir todos os metadados do teste, garantindo a reprodutibilidade em metodologias de simulação Renault.|
|RF11|O sistema deve permitir a configuração de parâmetros de aquisição, como taxa de amostragem dos sensores e duração dos testes.|As configurações devem ser aplicadas apenas antes do início de um teste, garantindo padronização para diferentes excitações veiculares e perfis de pista.

### 3.3.2. Requisitos Não Funcionais (sprint 2)	

_Descreva quais são os requisitos não funcionais e sua relação com aspectos de qualidade seguindo a norma ISO25010 (visão de aspectos de qualidade). Evolua estes requisitos conforme o desenvolvimento do projeto._

| **RNF#** | **Descrição** | **Aspecto de qualidade** | 
|----------|----------|----------|
|RNF01|Ex. O painel dashboard deve estar disponível 99% do tempo|Ex. Disponibilidade|
|RNF02|Preencha aqui seus requisitos|Preencha aqui o aspecto de qualidade|

### 3.3.3. Arquitetura da Solução (sprint 3)

_Vídeo de explicação sobre a arquitetura da solução: (coloque aqui o link do vídeo)_

_Descreva a arquitetura técnica da solução de forma detalhada (visão de arquitetura).

Justifique como a arquitetura suporta os requisitos funcionais e não funcionais.

O diagrama de arquitetura deve:_
- _Mostrar microcontroladores, incluindo descrições de sua função no sistema (por exemplo: "Irá processar o sinal dos sensores a cada X minutos")_
- _Mostrar sensores, incluindo descrição de função e especificações técnicas do tipo de informação que será coletada_
- _Mostrar apresentadores de informação (displays), incluindo descrição de que tipo de informação será apresentada (por exemplo, "Mostrar temperatura dos sensores")_
- _Mostrar atuadores, caso existam na solução, incluindo descrições do que irão acionar (por exemplo, "Ligar motor de irrigação durante x minutos")_
- _Mostrar o broker MQTT e o dashboard que é a interface do usuário_
- _Mostrar ligações entre os elementos (com fio ou sem fio) – incluindo conexões com sensores e atuadores, conexão com WiFi, entre outros_


### 3.3.4. Arquitetura do Protótipo(sprint 4)	

_Vídeo de explicação sobre a arquitetura do protótipo físico: (coloque aqui o link do vídeo)_

_Descreva as tecnologias utilizadas de forma detalhada (visão de tecnologia).

Descreva a arquitetura usando um diagrama de blocos similar à visão anterior, porém especificando as tecnologias utilizadas. O diagrama de arquitetura deve:_
- _Mostrar microcontroladores, incluindo descrições de sua função no sistema (por exemplo: "Irá processar o sinal dos sensores a cada X minutos")_
- _Mostrar sensores, incluindo descrição de função e especificações técnicas do tipo de informação que será coletada_
- _Mostrar apresentadores de informação (displays), incluindo descrição de que tipo de informação será apresentada (por exemplo, "Mostrar temperatura dos sensores")_
- _Mostrar atuadores, caso existam na solução, incluindo descrições do que irão acionar (por exemplo, "Ligar motor de irrigação durante x minutos")_
- _Mostrar o broker MQTT e o dashboard que é a interface do usuário_
- _Mostrar ligações entre os elementos (com fio ou sem fio) – incluindo conexões com sensores e atuadores, conexão com WiFi, entre outros._
_Faça uma tabela dos possíveis componentes utilizados. Todos os componentes devem estar presentes na arquitetura._

| **Componente** | **Descrição** | **Tipo** | 
|----------|----------|----------|
|E.g. ESP32 WROOM 32 Devkit|E.g. Trata-se de um microcontrolador amplamente usado na indústria e em projetos educacionais, que possui interfaces mais amigáveis para conexão de componentes diversos...|E.g. Microcontrolador|
|E.g. sensor XPTO|E.g. Este sensor mede o sinal de XYZ em unidades q/s, e possui tolerância de abcd...|E.g. Sensor|

### 3.3.5. Arquitetura Refinada da Solução (sprint 5)	

_Descreva a revisão da arquitetura técnica da solução de forma detalhada (visão de arquitetura). <br>

Justifique como a arquitetura suporta os requisitos funcionais e não funcionais. <br>

A revisão deverá incluir comentários sobre cada ponto levantado, mostrando como os ajustes foram realizados, além da descrição da arquitetura revisada._


## 3.4. Resultados	

_Nesta seção, detalhe os resultados obtidos com a implementação, de acordo com o disposto nas subseções._

### 3.4.1.Protótipo Inicial do Projeto usando o Simulador Wokwi (sprint 1)

_Preencha aqui o link para o protótipo inicial no Wokwi_

_Abaixo você deve registrar diversas situações de teste, indicando exemplos de leitura (entrada) e escrita (saída) apresentadas pelo seu sistema no simulador. Estes registros serão utilizados para testar seus componentes, portanto, descreva várias situações, incluindo não apenas casos de sucesso, mas também de possíveis falhas nas leituras de entradas e saídas. <br>
Siga as nomenclaturas e convenções já utilizadas anteriormente, e não se esqueça dos alinhamentos de negócios e experiência do usuário para pensar em situações representativas. Inclua figuras do simulador e descreva os testes realizados para ilustrar o funcionamento do protótipo simulado. A tabela a seguir serve como exemplo._

**#** | **Bloco** | **Componente de entrada** | **Leitura da entrada** | **Componente de saída** | **Leitura da saída** | **Descrição**
|----------|----------|----------|----------|----------|----------|----------|
|01|ex. medidor de umidade relativa do ar|ex. “sensor de umidade XPTO”| < 100 | ex. led amarelo | piscante em intervalo de 1s | quando a umidade está baixa, o led amarelo pisca

### 3.4.2. Protótipo Físico do Projeto (offline) (sprint 2)	

_Aqui você deve registrar diversas situações de teste, indicando exemplos de leitura (entrada) e escrita (saída) apresentadas pelo seu sistema físico. Estes registros serão utilizados para testar seus componentes, portanto, descreva várias situações, incluindo não apenas casos de sucesso, mas também de possíveis falhas nas leituras de entradas e saídas. <br>
Siga as nomenclaturas e convenções já utilizadas anteriormente, e não se esqueça dos alinhamentos de negócios e experiência do usuário para pensar em situações representativas. Inclua figuras do protótipo físico e descrições dos testes realizados para ilustrar o funcionamento do protótipo. A tabela a seguir serve como exemplo._

**#** | **Descrição** | **Pré-condição** | **Procedimento de teste** | **Pós-condição/Resultado esperado** | **Observações** (opcional)
|----------|----------|----------|----------|----------|----------|
|01|ex. Verificação de conexão de rede bem-sucedida. | ex. O dispositivo está desligado.| ex. Ligue o dispositivo, aguarde alguns segundos e verifique se ele estabelece uma conexão bem-sucedida com a rede Wi-Fi. | ex. O LED verde indicador de conexão acende de forma contínua, sinalizando uma conexão bem-sucedida à rede. |

### 3.4.3. Protótipo do Projeto com MQTT e I2C (sprint 3)	

_Aqui você deve registrar diversas situações de uso de seu sistema como um todo, indicando exemplos de ação do usuário e resposta do sistema, apontando como o ambiente deverá estar configurado para receber a ação e produzir a resposta. Estes registros serão utilizados para testar seu sistema, portanto, descreva várias situações, incluindo não apenas casos de sucesso, mas também de falha nos comportamentos do sistema. <br>
Siga as nomenclaturas e convenções já utilizadas anteriormente, e não se esqueça dos alinhamentos de negócios e experiência do usuário para pensar em situações representativas. Inclua figuras do protótipo físico e dashboards, além de descrições dos testes realizados para ilustrar o funcionamento do protótipo. A tabela a seguir serve como exemplo._

**#** | **Configuração do ambiente** | **Ação do usuário** | **Resposta esperada do sistema** 
|----------|----------|----------|----------|
|01|ex. precisa de um computador conectado na interface, dois ou mais dispositivos que simulem o posicionamento de um item X no espaço físico etc. | ex. usuário logado busca a localização do item X, que está ativo e operando normalmente | ex. interface do sistema acessa os dados da última localização registrada do item X e apresenta, constando local e horário de última atualização | 

### 3.4.4. Protótipo Físico do Projeto (online) (sprint 4)	

_Aqui você deve registrar diversas situações de uso de seu sistema como um todo, indicando exemplos de ação do usuário e resposta do sistema, apontando como o ambiente deverá estar configurado para receber a ação e produzir a resposta. Estes registros serão utilizados para testar seu sistema, portanto, descreva várias situações, incluindo não apenas casos de sucesso, mas também de falha nos comportamentos do sistema. <br>
**Desta vez, utilize diagramas de sequência UML para descrever os fluxos de teste do sistema.** <br>
Siga as nomenclaturas e convenções já utilizadas anteriormente, e não se esqueça dos alinhamentos de negócios e experiência do usuário para pensar em situações representativas. Inclua figuras do protótipo físico e dashboards, além de descrições dos testes realizados para ilustrar o funcionamento do protótipo._

### 3.4.5. Protótipo Final do Projeto (sprint 5)	

_Registre as situações de uso do sistema revisadas utilizando a modelagem UML para descrever os fluxos de teste. <br>
Também inclua figuras da versão final do protótipo físico e dashboards, além de descrições dos testes realizados para ilustrar o funcionamento do protótipo._

## <a name="c4"></a>4. Conclusões e Recomendações

_Escreva, de forma resumida, sobre os principais resultados do seu projeto e faça recomendações formais ao seu parceiro de projeto em relação ao uso dessa solução. Você pode aproveitar este espaço para comentar sobre possíveis materiais extras._

## <a name="c5"></a>5. Referências


KEVIN DUNNE. SWOT Analysis: Strengths, Weaknesses, Opportunities and Threats (ou título equivalente em inglês conforme aparece na página). Mind Tools, sem data explícita de publicação (s.d.). Acesso em: 19 out. 2025.

BRUTON, Louise. What are UX personas and what are they used for? UX Design Institute, 2022. Disponível em: https://www.uxdesigninstitute.com/blog/what-are-ux-personas/. Acesso em: 19 out. 2025.

KOTONYA, Gerald; SOMMERVILLE, Ian. Requirements engineering: processes and techniques. Chichester: J. Wiley, 1998.

WIEGERS, Karl; BEATTY, Joy. Software requirements. 3. ed. Redmond: Microsoft Press, 2013.
