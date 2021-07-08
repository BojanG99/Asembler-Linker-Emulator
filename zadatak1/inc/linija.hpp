class labela;
class asemblerskaDirektiva;
class naredbe;
class linija
{
private:
    labela * l;
    naredbe* naredba;
    asemblerskaDirektiva * dir;
public:
    linija(/* args */);
    ~linija();
    labela*  dohvati_Labelu(){
        return l;
    }
    asemblerskaDirektiva* dohvati_Direktivu(){
        return dir;
    }
    naredbe* dohvati_Naredbu(){
        return naredba;
    }
    void postavi_Labelu(labela* lab){
        l=lab;
    }
    void postavi_Direktivu(asemblerskaDirektiva* d){
        dir=d;
    }
    void postavi_Naredbu(naredbe*nar){
        naredba=nar;
    }
};

