#include <string>
#include <iostream>
#include <random>
using namespace std;
int main()
{
    random_device rd;
    mt19937 gen(rd());
    int min, max, desa;
    int escravos, pleto;
    string fatorDecisórioDeDireitos, verda, drogas, anabolizantes;
    bool fracassado= false;
    desa = 0;
    escravos = 20;
    pleto = 0;
    drogas = "";

    cout << "\nDefine nivel de dificuldade \nPussy = 1\nNormal = 2\nImpossivel = 3\nDesenvolvedor = 4\n";
    cin >> desa;
    
    
    if( desa == 1)
    {
        while(fracassado != true)
        {
        cout << "tens " << escravos << " talões de escravos\n";
        min = 1;
        max = 3;
        uniform_int_distribution<> dis(min, max);
        int manke = dis(gen);
        if(manke%2 == 0 && manke != 3 ) verda = "vermelho";
        if(manke%2 != 0 && manke != 3 ) verda = "azul";
        if(manke == 3) verda = "verde";
        cout << "Quanto queres apostar?\n";
        cin >> pleto;
        if(pleto > escravos)
        {
            cout << "Não tens esses talões, seu troglodita burro de merda\nInsere outro valor dentro dos limites do teu saldo\n";
            cin >> pleto;
            if(pleto > escravos)
            {
                cout << "O teu cu foi comido e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer pika\nQueres pika!\n";
                break;
            }     
        }
        cout << "Em que cor apostas:\nvermelho \nazul \nverde\n";
        cin >> fatorDecisórioDeDireitos;
        if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
        {
            cout << "És burro ou anormal?\nInsere uma das cores\n";
            cin >> fatorDecisórioDeDireitos;
            if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer menores\nQueres menores!\n";
                break;
            }     
        }
        cout << "Número aleatório: " << manke << "\n";
        if(fatorDecisórioDeDireitos == verda )
        {
            cout << "U sortudo\n";
            escravos += (2 * pleto);
        }
        if(fatorDecisórioDeDireitos != verda)
        {
            cout << "U burro, U perdeu escravos\n";
            escravos -= pleto;
        }

        if(escravos <= 0)
        {
            cout << "ficaste sen dinelo, go back to china, get a job, gain cash, and came back\n";
            fracassado = true;
            break;
        }

        cout << "Sua alteza deseja continuar aa apostar o seu belissimo orificio anal neste jogo divinal?\nsim\nnão\n";
        cin >> anabolizantes;
        if(anabolizantes != "sim" && anabolizantes != "não")
        {
            cout << "Éliteralmente uma pergunta de sim ou não, responde direito!\nsim ou não?\n";
            cin >> anabolizantes;
            if(anabolizantes != "sim" && anabolizantes != "não")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer conchecer o apreciador infantil aka eu aka Bruno Lemos\nQueres morrer animal burro de merda!\n";
                break;
            }     
        }
        if( anabolizantes == "não")
        {
            cout << "doki oki miss ";
            fracassado = true;
        }

        
        
        }
    }
        if( desa == 2)
    {
        while(fracassado != true)
        {
        cout << "tens " << escravos << " talões de escravos\n";
        min = 1;
        max = 100;
        uniform_int_distribution<> dis(min, max);
        int manke = dis(gen);
        if(manke%2 == 0 && manke != 100 ) verda = "vermelho";
        if(manke%2 != 0 && manke != 100 ) verda = "azul";
        if(manke == 100) verda = "verde";
        cout << "Quanto queres apostar?\n";
        cin >> pleto;
        if(pleto > escravos)
        {
            cout << "Não tens esses talões, seu troglodita burro de merda\nInsere outro valor dentro dos limites do teu saldo\n";
            cin >> pleto;
            if(pleto > escravos)
            {
                cout << "O teu cu foi comido e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer pika\nQueres pika!\n";
                break;
            }     
        }
        cout << "Em que cor apostas:\nvermelho \nazul \nverde\n";
        cin >> fatorDecisórioDeDireitos;
        if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
        {
            cout << "És burro ou anormal?\nInsere uma das cores\n";
            cin >> fatorDecisórioDeDireitos;
            if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer menores\nQueres menores!\n";
                break;
            }     
        }
        cout << "Número aleatório: " << manke << "\n";
        if(fatorDecisórioDeDireitos == verda )
        {
            cout << "U sortudo\n";
            escravos += (2 * pleto);
        }
        if(fatorDecisórioDeDireitos != verda)
        {
            cout << "U burro, U perdeu escravos\n";
            escravos -= pleto;
        }

        if(escravos <= 0)
        {
            cout << "ficaste sen dinelo, go back to china, get a job, gain cash, and came back\n";
            fracassado = true;
            break;
        }

        cout << "Sua alteza deseja continuar aa apostar o seu belissimo orificio anal neste jogo divinal?\nsim\nnão\n";
        cin >> anabolizantes;
        if(anabolizantes != "sim" && anabolizantes != "não")
        {
            cout << "Éliteralmente uma pergunta de sim ou não, responde direito!\nsim ou não?\n";
            cin >> anabolizantes;
            if(anabolizantes != "sim" && anabolizantes != "não")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer conchecer o apreciador infantil aka eu aka Bruno Lemos\nQueres morrer animal burro de merda!\n";
                break;
            }     
        }
        if( anabolizantes == "não")
        {
            cout << "doki oki miss ";
            fracassado = true;
        }

        
        
        }
    }
        if( desa == 3)
    {
        while(fracassado != true)
        {
        cout << "tens " << escravos << " talões de escravos\n";
        min = 1;
        max = 1000000;
        uniform_int_distribution<> dis(min, max);
        int manke = dis(gen);
        if(manke%2 == 0 && manke != 1000000 ) verda = "vermelho";
        if(manke%2 != 0 && manke != 1000000 ) verda = "azul";
        if(manke == 1000000) verda = "verde";
        cout << "Quanto queres apostar?\n";
        cin >> pleto;
        if(pleto > escravos)
        {
            cout << "Não tens esses talões, seu troglodita burro de merda\nInsere outro valor dentro dos limites do teu saldo\n";
            cin >> pleto;
            if(pleto > escravos)
            {
                cout << "O teu cu foi comido e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer pika\nQueres pika!\n";
                break;
            }     
        }
        cout << "Em que cor apostas:\nvermelho \nazul \nverde\n";
        cin >> fatorDecisórioDeDireitos;
        if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
        {
            cout << "És burro ou anormal?\nInsere uma das cores\n";
            cin >> fatorDecisórioDeDireitos;
            if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer menores\nQueres menores!\n";
                break;
            }     
        }
        cout << "Número aleatório: " << manke << "\n";
        if(fatorDecisórioDeDireitos == verda )
        {
            cout << "U sortudo\n";
            escravos += (2 * pleto);
        }
        if(fatorDecisórioDeDireitos != verda)
        {
            cout << "U burro, U perdeu escravos\n";
            escravos -= pleto;
        }

        if(escravos <= 0)
        {
            cout << "ficaste sen dinelo, go back to china, get a job, gain cash, and came back\n";
            fracassado = true;
            break;
        }

        cout << "Sua alteza deseja continuar aa apostar o seu belissimo orificio anal neste jogo divinal?\nsim\nnão\n";
        cin >> anabolizantes;
        if(anabolizantes != "sim" && anabolizantes != "não")
        {
            cout << "Éliteralmente uma pergunta de sim ou não, responde direito!\nsim ou não?\n";
            cin >> anabolizantes;
            if(anabolizantes != "sim" && anabolizantes != "não")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer conchecer o apreciador infantil aka eu aka Bruno Lemos\nQueres morrer animal burro de merda!\n";
                break;
            }     
        }
        if( anabolizantes == "não")
        {
            cout << "doki oki miss ";
            fracassado = true;
        }

        
        
        }
    }
    if(desa == 4)
    {
        cout << "stfu nigga u not me, me can, u not\n";
        escravos = 0;
    }
        if( desa == 9)
    {
        while(fracassado != true)
        {
        cout << "tens " << escravos << " talões de escravos\n";
        
        int manke = 3;
        if(manke%2 == 0 && manke != 0 ) verda = "vermelho";
        if(manke%2 != 0 && manke != 0 ) verda = "azul";
        if(manke == 3) verda = "verde";
        cout << "Quanto queres apostar?\n";
        cin >> pleto;
        if(pleto > escravos)
        {
            cout << "Não tens esses talões, seu troglodita burro de merda\nInsere outro valor dentro dos limites do teu saldo\n";
            cin >> pleto;
            if(pleto > escravos)
            {
                cout << "O teu cu foi comido e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer pika\nQueres pika!\n";
                break;
            }     
        }
        cout << "Em que cor apostas:\nvermelho \nazul \nverde\n";
        cin >> fatorDecisórioDeDireitos;
        if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
        {
            cout << "És burro ou anormal?\nInsere uma das cores\n";
            cin >> fatorDecisórioDeDireitos;
            if(fatorDecisórioDeDireitos != "vermelho" && fatorDecisórioDeDireitos != "verde" && fatorDecisórioDeDireitos != "azul")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer menores\nQueres menores!\n";
                break;
            }     
        }
        cout << "Número aleatório: " << manke << "\n";
        if(fatorDecisórioDeDireitos == verda )
        {
            cout << "U sortudo\n";
            escravos += (2 * pleto);
        }
        if(fatorDecisórioDeDireitos != verda)
        {
            cout << "U burro, U perdeu escravos\n";
            escravos -= pleto;
        }

        if(escravos <= 0)
        {
            cout << "ficaste sen dinelo, go back to china, get a job, gain cash, and came back\n";
            fracassado = true;
            break;
        }

        cout << "Sua alteza deseja continuar aa apostar o seu belissimo orificio anal neste jogo divinal?\nsim\nnão\n";
        cin >> anabolizantes;
        if(anabolizantes != "sim" && anabolizantes != "não")
        {
            cout << "Éliteralmente uma pergunta de sim ou não, responde direito!\nsim ou não?\n";
            cin >> anabolizantes;
            if(anabolizantes != "sim" && anabolizantes != "não")
            {
                cout << "O teu cu foi deliciado pelo degustador e foste expulso\nUm sávio uma vez disse, à primeira caem os distraídos, na segunda só cai quem quer conchecer o apreciador infantil aka eu aka Bruno Lemos\nQueres morrer animal burro de merda!\n";
                break;
            }     
        }
        if( anabolizantes == "não")
        {
            cout << "doki oki miss ";
            fracassado = true;
        }

        }
    }
    
    if(escravos != 0)
    {
        cout << "No final tibéstê " << escravos << " escravos muy bien\n";
    }
    
    cout <<" perdeste tudo és burro, analfabeto, pobre, burro, burro, ficaste com " << escravos << " na conta\n";
}