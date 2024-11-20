# BP - Edge

## Descrição do Projeto
Esse projeto busca abordar a necessidade de soluções de energias renováveis acessíveis principalmente em áreas mais carentes, utilizando sistemas embarcados para prototipagem e monitoramento de dados de desempenho de coleta e armazenamento de energia solar. A composição básica dele é a prototipagem através de dois LDRs que simulam a coleta de energia solar, o projeto se comunica com o FIWARE através de um serviço cloud que armazena os dados através do Módulo STH Comet do próprio FIWARE, essas informações são informadas no [Front End](https://github.com/Bright-Path-Team/bp-front) da Bright Path.

## Circuito
### Componentes utilizados
- x1 ESP32: Microcontrolador principal que gerencia os sensores e envia os dados para o FIWARE.;
- x1 Protoboard: Uma placa de ensaio usada para montar circuitos eletrônicos temporariamente sem necessidade de solda. Ideal para prototipagem e testes rápidos;
- x2 LDR: Sensores que alteram sua resistência com base na intensidade da luz. São usados para medir luminosidade ou detectar variações de luz em um ambiente;
- x1 Servo Motor: Motor de controle de precisão que pode ser ajustado para um ângulo específico. Comumente utilizado em aplicações de movimento controlado, como ajuste da posição de placas solares;
- x1 Barra gráfica Led: Um conjunto de LEDs dispostos em linha, geralmente usados para indicar valores em forma de gráfico de barras, como nível de luz ou energia;
- x1 74hc595: Um circuito integrado shift register utilizado para expandir as saídas digitais de um microcontrolador. É ideal para controlar vários LEDs ou outros componentes com um número limitado de pinos;
- x9 Resistores de 180 Ω: Resistores com resistência de 180 ohms, usados para limitar a corrente elétrica em LEDs ou outros componentes, protegendo-os de danos;

- Para mais informações de montagem, você pode utilizar o Wokwi - Acesse o [diagram.json](/diagram.json) para mais informações!

### Manual de utilização
- Crie uma máquina Virtual (local ou no cloud) para fazer o uso do docker - recomendado utilizar o linux;
- Realize a instalação Fiware ou o [FIWARE Descomplicado](https://github.com/fabiocabrini/fiware);
- Com o FIWARE instalado, devemos transformar esse módulos em serviços, utilizando o [Docker](https://www.docker.com/);
- Após a instalação do docker e modularização do serviços, utilize o comando `sudo docker compose up -d` para inicializar o Docker;
- Realize a configuração de sua [collection](https://github.com/fabiocabrini/fiware/blob/main/FIWARE%20Descomplicado.postman_collection.json) (recomendação: Postman);
- Faça as devidas alterações no [sketch.ino](/sketch.ino) de acordo com a lógica de seu programa e os dispositivos IoT que serão utilizados;

### Arquitetura do projeto
![architecture](https://github.com/user-attachments/assets/60c8cd75-7416-4107-9f3f-bd73ed70b870)

## Painel STH no LINUX (Dashboard)
1 - Realize o download do arquivo [api-sth.py](/api-sth.py) em um diretório do linux; <br>
2 - Utilize um ambiente virtual para evitar realizar o download de bibliotecas em excesso em sua máquina - `python -m venv venv`; <br>
3 - Acesse o ambiente virtual `source venv/bin/activate` e realize o download das bibliotecas necessárias: `pip install dash plotly requests pytz datetime`; <br>
4 - Saia do ambiente virtual: `deactivate`; <br>
5 - Utilize o comando `python3 api-sth.py`;

> [!WARNING]  
> Sempre que fechar o terminal que está conectado na máquina, o Dashboard irá parar de funcionar, para isso, iremos criar um serviço, utilizando o Daemon.

### Criação do serviço Daemon
1 - Navegue até o diretório `/etc/systemd/system` e crie um arquivo com a extensão `.service` -> `sudo nano /etc/systemd/system/api-sth.service`; <br>
2 - Preencha esse arquivo .service com as seguintes informações:
```bash
[Unit]
Description=Descrição do serviço                            # Coloque aqui uma descrição para melhor identificação do serviço
After=network.target                                        # network.target se refere a um serviço do Linux de rede

[Service]
Type=simple                                                 # Tipo de serviço
User=azureuser                                              # Usuário que está com as configurações do api-sth.py
ExecStart=/usr/local/bin/python /app/in/python/directory    # O primeiro se refere ao diretório do python, o ultimo, o diretório em que o arquivo api-sth.py se encontra
Restart=always                                              # Sempre que houver um erro com o serviço, ele irá reiniciar/inicializar automaticamente

[Install]
WantedBy=multi-user.target                                  # Define que o serviço será iniciado automaticamente no sistema
```
3 - Reinicie o daemon -> `sudo systemctl daemon-reload`; <br>
4 - Verifique o status de seu serviço `sudo systemctl status api-sth.service` e inicialize-o se necessário `sudo systemctl start api-sth.service`; <br>
5 - Para ter total certeza de que o serviço irá inicializar com o Linux, utilize o comando `sudo systemctl enable api-sth.service`;

## Desenvolvedores do projeto:

| **Nome** | **RM**                 | **LinkedIn** |
|--------------------------------|------------------------|----------|
| Murilo Justi                   | RM 554512              | <a target="_blank" href="https://www.linkedin.com/in/murilo-justi-rodrigues-b336b22b7/"><img src="https://media.licdn.com/dms/image/v2/D4D03AQGnXBOl96aCtQ/profile-displayphoto-shrink_800_800/profile-displayphoto-shrink_800_800/0/1709252884484?e=1733961600&v=beta&t=_W2l37rEiTdk8HSG-GUrS4R_V6KddfAGj13CbkA_k0g" width="80"></a> |
| Renan Dias Utida               | RM 558540              | <a target="_blank" href="https://www.linkedin.com/in/renan-dias-utida-1b1228225/"><img src="https://media.licdn.com/dms/image/v2/D4D03AQHZyF9WkCRtDg/profile-displayphoto-shrink_800_800/profile-displayphoto-shrink_800_800/0/1727923002401?e=1733961600&v=beta&t=foOm4Ar-LZJK6z8mu_ypyoXfkqYesw3MAc4acpeAqpU" width="80"></a> |
| Leonardo Rocha Scarpitta       | RM 555460              | <a target="_blank" href="https://www.linkedin.com/in/leonardorscarpitta/"><img src="https://avatars.githubusercontent.com/u/161969345?s=400&u=f9bdb6fa659af646efcd0cb9fb51a321f19faabc&v=4" width="80"></a> |

## Licença

Este projeto é open source sob a **MIT License with Commons Clause**. Isso significa que você pode visualizar, modificar e compartilhar o código livremente, desde que não o utilize para fins comerciais.

Para mais detalhes, consulte o arquivo [LICENSE](./LICENSE).
