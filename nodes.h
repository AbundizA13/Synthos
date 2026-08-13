#include "neonexus.h"

class Nodo{
    public:
        Nodo(Token t, Nodo* a, Nodo* b)
            : token(t), izq(a), der(b), padre(nullptr){}
        virtual ~Nodo() = default;
        Nodo* izq;
        Nodo* der;
        Nodo* padre;
        token token;
        virtual double evaluar(ContextoEvaluator& contexto) = 0;
};

class Nodo_Numero : public Nodo{
    public:
        using Nodo::Nodo;
        double evaluar(ContextoEvaluator& contexto) override;
};

class Nodo_Variable : public Nodo{
    public:
        using Nodo::Nodo;
        double evaluar(ContextoEvaluator& contexto) override;
};

class Nodo_Funcion : public Nodo{
    public:
        using Nodo::Nodo;
        double evaluar(ContextoEvaluator& contexto) override;
};

class Nodo_Operador : public Nodo{
    private:
        double valor_izquierdo = 0.0;
        double valor_derecho = 0.0;
    public:
        using Nodo::Nodo;
        double evaluar(ContextoEvaluator& contexto) override;
};

class Nodo_Operador_Unario : public Nodo{
    private:
        double valor = 0.0;
    public:
        using Nodo::Nodo;
        double evaluar(ContextoEvaluator& contexto) override;
};