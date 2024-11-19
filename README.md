# BP - Edge

## Descrição do Projeto
Esse projeto de sistemas embarcados foi desenvolvido utilizando C++ com o objetivo de simular placas solares que levam energias a áreas mais carentes da energia elétrica ou então de energias renováveis. A composição básica dele é a prototipagem através de dois LDRs que simulam a coleta de energia solar, o projeto se comunica com o FIWARE através de um serviço cloud que armazena os dados através do Módulo STH Comet do próprio FIWARE, essas informações são informadas no [Front End](https://github.com/Bright-Path-Team/bp-front) da Bright Path.

## Componentes utilizados
- x1 ESP32;
- x1 Protoboard;
- x2 LDR;
- x1 Servo Motor;
- x1 Barra gráfica Led;
- x1 74hc595;
- x9 Resistores de 180 Ω;

- Para mais informações de montagem, você pode utilizar o Wokwi - Acesse o [diagram.json](/diagram.json) para mais informações!

## Manual de instalação
- Crie uma máquina Virtual (local ou no cloud) para fazer o uso do docker - recomendado utilizar o linux;
- Realize a instalação Fiware ou o [FIWARE Descomplicado](https://github.com/fabiocabrini/fiware);
- Com o FIWARE instalado, devemos transformar esse módulos em serviços, utilizando o [Docker](https://www.docker.com/);
- Após a instalação do docker e modularização do serviços, utilize o comando `sudo docker compose up -d` para inicializar o Docker;
- Realize a configuração de sua [collection](https://github.com/fabiocabrini/fiware/blob/main/FIWARE%20Descomplicado.postman_collection.json) (recomendação: Postman);
- Faça as devidas alterações no [sketch.ino](/sketch.ino) de acordo com a lógica de seu programa e os dispositivos IoT que serão utilizados;

## Desenvolvedores do projeto:

| **Nome** | **RM**                 | **LinkedIn** |
|--------------------------------|------------------------|----------|
| Murilo Justi                   | RM 554512              | <a target="_blank" href="https://www.linkedin.com/in/murilo-justi-rodrigues-b336b22b7/"><img src="https://media.licdn.com/dms/image/v2/D4D03AQGnXBOl96aCtQ/profile-displayphoto-shrink_800_800/profile-displayphoto-shrink_800_800/0/1709252884484?e=1733961600&v=beta&t=_W2l37rEiTdk8HSG-GUrS4R_V6KddfAGj13CbkA_k0g" width="80"></a> |
| Renan Dias Utida               | RM 558540              | <a target="_blank" href="https://www.linkedin.com/in/renan-dias-utida-1b1228225/"><img src="https://media.licdn.com/dms/image/v2/D4D03AQHZyF9WkCRtDg/profile-displayphoto-shrink_800_800/profile-displayphoto-shrink_800_800/0/1727923002401?e=1733961600&v=beta&t=foOm4Ar-LZJK6z8mu_ypyoXfkqYesw3MAc4acpeAqpU" width="80"></a> |
| Leonardo Rocha Scarpitta       | RM 555460              | <a target="_blank" href="https://www.linkedin.com/in/leonardorscarpitta/"><img src="https://avatars.githubusercontent.com/u/161969345?s=400&u=f9bdb6fa659af646efcd0cb9fb51a321f19faabc&v=4" width="80"></a> |

## Licença

Este projeto é open source sob a **MIT License with Commons Clause**. Isso significa que você pode visualizar, modificar e compartilhar o código livremente, desde que não o utilize para fins comerciais.

Para mais detalhes, consulte o arquivo [LICENSE](./LICENSE).
