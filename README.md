# Inteli - Instituto de Tecnologia e Liderança

<p align="center">
<a href= "https://www.inteli.edu.br/"><img src="assets/inteli.png" alt="Inteli - Instituto de Tecnologia e Liderança" border="0" width=40% height=40%></a>
</p>

<br>

# Rythmo IoT

## Rythmo

## 👨‍🎓 Integrantes:

- <a href="https://www.linkedin.com/in/antoniodicillo/">Antonio Di Cillo</a>
- <a href="https://github.com/CaduQuaglia">Carlos Quaglia
  </a>
- <a href="https://www.linkedin.com/in/caue-taddeo-956194362/">Caue Taddeo
  </a>
- <a href="https://www.linkedin.com/in/gabriel-bartmanovicz/">Gabriel Bartmanovicz
  </a>
- <a href="https://www.linkedin.com/in/rafael-santana-rodrigues/">Rafael Santana Rodrigues
  </a>
- <a href="https://github.com/thuliobacco/">Thulio Bacco
  Pinto</a>

## 👩‍🏫 Professores:

### Orientador(a)

- <a href="https://www.linkedin.com/in/profclaudioandre/">Claudio Andre
  </a>

### Instrutores

- <a href="https://www.linkedin.com/in/anacristinadossantos/">Ana Cristina dos Santos
  </a>
- <a href="https://www.linkedin.com/in/andregodoichiovato/">André Godoi
  </a>
- <a href="https://www.linkedin.com/in/bruna-mayer/">Bruna Mayer
  </a>
- <a href="https://www.linkedin.com/in/geraldo-magela-severino-vasconcelos-22b1b220/">Geraldo Vasconcelos</a>
- <a href="https://www.linkedin.com/in/rafael-jacomossi-6135b0a1/">Rafael Jacomossi
  </a>

## 📜 Descrição

O projeto Rythmo desenvolve uma solução IoT para a Renault do Brasil voltada à coleta e análise de dados de aceleração e força em veículos de teste. O sistema utiliza sensores acelerômetros e piezoelétricos embarcados para capturar informações em tempo real durante testes de rodagem em diferentes tipos de pista. Esses dados são transmitidos via protocolo MQTT através de conexão Wi-Fi e armazenados em um banco de dados relacional na nuvem, permitindo a criação de uma base padronizada para simulações de Squeak and Rattle (ruídos e vibrações estruturais). A interface web oferece visualização interativa dos dados coletados, incluindo metadados como tipo de pista, velocidade do veículo e condições climáticas, garantindo rastreabilidade completa do processo de coleta.

A solução busca resolver a falta de dados estruturados para análises do tipo "e-line", que dependem de sinais precisos de deslocamento e força ao longo do tempo. Com a implementação deste sistema, espera-se reduzir significativamente o tempo e os custos associados aos testes físicos, aumentar a precisão das análises de engenharia e identificar antecipadamente falhas estruturais nos veículos. O projeto contribui para a inovação nos processos de desenvolvimento automotivo da Renault, alinhando-se às tendências de digitalização e automação da indústria, além de estabelecer uma base sólida para futuras análises reprodutíveis e construção de sinais de entrada genéricos para estudos de Squeak and Rattle.


**Diferenciais**
- Coleta de dados em tempo real com sensores avançados.
- Transmissão eficiente via MQTT.
- Armazenamento estruturado em banco de dados na nuvem.
- Interface web interativa para visualização de dados.

Link do vídeo de demonstração do projeto:
https://youtu.be/NFCR8O2e0Go

## 📁 Estrutura de pastas

Dentre os arquivos e pastas presentes na raiz do projeto, definem-se:

- <b>assets</b>: aqui estão os arquivos relacionados a parte gráfica do projeto, ou seja, as imagens e vídeos que os representam (O logo do grupo pode ser adicionado nesta pasta).

- <b>document</b>: aqui estão todos os documentos do projeto, incluindo o manual de instruções (se aplicável). Há também uma pasta denominada <b>outros</b> onde estão presentes outros documentos complementares.

- <b>src</b>: Todo o código fonte criado para o desenvolvimento do projeto, incluindo firmware, notebooks, backend e frontend, se aplicáveis.

- <b>README.md</b>: arquivo que serve como guia e explicação geral sobre o projeto (o mesmo que você está lendo agora).

```
├── assets
│   ├── 5-forcas.png
│   ├── analiseSWOT.png
│   ├── arquitetura-solucao.png
│   ├── arquitetura.png
│   ├── canvas-proposta-de-valor.png
│   ├── caso-de-teste1.png
│   ├── caso-teste-10.png
│   ├── caso-teste-11.png
│   ├── caso-teste-147.png
│   ├── caso-teste-258.png
│   ├── caso-teste-369.png
│   ├── circuito-rc-1.jpeg
│   ├── circuito-rc-2.jpeg
│   ├── circuito-rc-3.jpeg
│   ├── grafico-rc-cap.png
│   ├── grafico.png
│   ├── graficoCorrigido.png
│   ├── image.png
│   ├── ImagemDoPrototipo.png
│   ├── ImagemUbidots.png
│   ├── inteli.png
│   ├── jornada-joao-silva-current.png
│   ├── jornada-joao-silva-future.png
│   ├── jornada-maria-oliveira-future.png
│   ├── matriz-de-riscos.png
│   ├── mpu-error.png
│   ├── persona-1.png
│   ├── persona-2.png
│   ├── rm-odp.png
│   ├── storyboard-joao.png
│   ├── storyboard-maria.png
│   ├── tabela-ocorrências.jpeg
│   └── TaxaDeAtualizacao.png
├── diagram.json
├── document
│   ├── documentacao.md
│   ├── manual-de-instrucoes.pdf
│   └── outros
│       ├── dados.csv
│       └── grafico.ipynb
├── platformio.ini
├── README.md
├── src
│   └── firmware
│       └── prog.ino
└── wokwi.toml
```

## 🔧 Instalação

Segue a estrutura atualizada incluindo as informações de **pré-requisitos** e **instalação básica** do projeto, descrevendo as versões utilizadas para cada ferramenta:

### Pré-requisitos

Para configurar e executar o projeto corretamente, certifique-se de ter os seguintes itens instalados no seu ambiente de desenvolvimento:

1. **Ambientes de Desenvolvimento**:

   - **Arduino IDE** (versão 2.1 ou superior):
     - Usada para programar os sensores IoT e o firmware.
     - Download: [Arduino IDE](https://www.arduino.cc/en/software)

2. Versões Utilizadas: 
    - Arduino IDE: 2.1.0
    - VSCode: 1.80
    - Placa ESP32: Espressif Systems ESP32 Dev Module
    - Plataforma Ubidots: Conta gratuita para visualização de dados IoT
  - 
3. **Conexão com Hardware**
  
- Conecte os sensores na placa ESP32 conforme o guia no diretório `document/manual-de-instrucoes.pdf`.
- Verifique as leituras iniciais via Monitor Serial no Arduino IDE e pela plataforma Ubidots.

### Instalação Básica
1. Clone este repositório para o seu ambiente local:
   ```bash
   git clone https://github.com/Inteli-College/2025-2B-T15-IN04-G03.git
   ```  
2. Navegue até o diretório do projeto:
   ```bash
   cd 2025-2B-T15-IN04-G03
    ```
3. Abra o arquivo `prog.ino` localizado em `src/firmware/` com o Arduino IDE.
4. Instale as bibliotecas necessárias no Arduino IDE:
   - Vá para `Sketch` > `Include Library` > `Manage Libraries...`
   - Procure e instale as bibliotecas descritas no manual de instruções.
5. Configure as credenciais Wi-Fi e as configurações do MQTT no código-fonte conforme o manual de instruções.
6. Faça o upload do código para a placa ESP32.
7. Monitore os dados coletados via Monitor Serial e na plataforma Ubidots.

**Manual de Instruções:** acesse o arquivo `manual-de-instrucoes.pdf` na pasta `document`.


## 🗃 Histórico de lançamentos

* 0.1.0 - 24/10/2023
  
Fundamentos de negócio, experiência de usuário, protótipo inicial wokwi, requisitos Funcionais

 * 0.2.0 - 07/11/2023

Protótipo físico do projeto, requisitos não funcionais, jornada do usuário e storyboard

* 0.3.0 - 19/11/2023

Protótipo do Projeto com MQTT e I2C, metodologia e arquitetura da solução

 * 0.4.0 - 05/12/2023

Protótipo físico do projeto (online), Código do projeto, Manual de Instruções, Arquitetura do protótipo e Possibilidades de descarte

* 0.5.0 - 19/12/2023

Código do projeto (versão final), Arquitetura refinada da solução, Manual de instruções revisado e Protótipo final do projeto

## 📋 Licença/License

<img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/cc.svg?ref=chooser-v1"><img style="height:22px!important;margin-left:3px;vertical-align:text-bottom;" src="https://mirrors.creativecommons.org/presskit/icons/by.svg?ref=chooser-v1"><p xmlns:cc="http://creativecommons.org/ns#" xmlns:dct="http://purl.org/dc/terms/"><a property="dct:title" rel="cc:attributionURL" href="https://github.com/Intelihub/Template_M2/"><a href="https://github.com/Inteli-College/2025-2B-T15-IN04-G03">Rythmo</a> © 2025 by <a href="https://github.com/Inteli-College/2025-2B-T15-IN04-G03">INTELI, Antonio Di Cillo, Carlos Quaglia, Caue Taddeo, Gabriel Bartmanovicz, Rafael Santana Rodrigues, Thulio Bacco Pinto.</a> is licensed under <a href="https://creativecommons.org/licenses/by/4.0/">Creative Commons Attribution 4.0 International</a>.
