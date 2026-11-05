#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

//EJEMPLO DE USO
// delegate<void()> d0;
//
// d0 += Aux0_;
// d0 += Aux2_;
// d0 += Aux1_;
//
// d0 ();

// Lvalue: un objeto que tiene identidad y puede identificarse mediante una dirección. Por ejemplo, una variable.
//
// Rvalue: un valor temporal o que puede tratarse como tal. Por ejemplo, 10 o el resultado de determinadas operaciones.

//declaración de la plantilla, es decir el tipo de funcion que se almacena void(), void(int), void(int,int)
// Declaración adelantada de la plantilla delegate.
// Signature representa la firma de la función que almacenará el delegate.
template <typename Signature>
struct delegate;

//typename... Args es un parameter pack, es decir, permite recibir cero o más tipos.
// Especialización parcial para funciones que devuelven void
// y reciben cero o más parámetros Args.
template <typename... Args>
struct delegate<void(Args...)>
{
    //clase base
    // Su función es establecer una interfaz común para todos los callbacks.
    struct base
    {
        virtual ~base()
        {
        }

        // Compara el callback actual con otro callback.
        //se necesita porque queremos almacenar callbacks de distintos tipos dentro del mismo vector. y tambien lambdas
        //[]() { /* código */ }
        virtual bool do_cmp(base* other) = 0;
        // Ejecuta el callback almacenado.
        virtual void do_call(Args... args) = 0;
    };

    // Clase derivada que almacena un callback concreto.
    template <typename T>
    struct call : base
    {
        T d_callback;

        // Constructor que inicializa el callback mediante
        // copia o movimiento, dependiendo del argumento recibido.
        //S&&: referencia universal (referencia de reenvío, en este contexto).
        //std::forward<S>(): permite conservar la categoría de valor del argumento original, copiándolo o moviéndolo 
        //según corresponda.
        template <typename S>
        call(S&& callback) : d_callback(std::forward<S>(callback))
        {
        }

        // Comprueba si el otro objeto es del mismo tipo de callback
        // y, si lo es, compara los callbacks almacenados.
        bool do_cmp(base* other)
        {
            call<T>* tmp = dynamic_cast<call<T>*>(other);
            return tmp && this->d_callback == tmp->d_callback;
        }

        // Invoca el callback almacenado pasando los argumentos recibidos.
        void do_call(Args... args)
        {
            return this->d_callback(std::forward<Args>(args)...);
        }
    };

    // Contenedor que almacena los callbacks mediante punteros inteligentes.
    std::vector<std::unique_ptr<base>> d_callbacks;

    // Se prohíbe copiar el delegate.
    delegate(delegate const&) = delete;
    void operator=(delegate const&) = delete;

public:
    delegate()
    {
    }

    // Sobrecarga del operador += para añadir un callback al delegate.
    template <typename T>
    delegate& operator+=(T&& callback)
    {
        this->d_callbacks.emplace_back(new call<T>(std::forward<T>(callback)));
        return *this;
    }

    // Sobrecarga del operador -= para eliminar un callback del delegate.
    template <typename T>
    delegate& operator-=(T&& callback)
    {
        call<T> tmp(std::forward<T>(callback));

        // Busca los callbacks que coinciden con el recibido
        // y los elimina del vector.
        auto it = std::remove_if(this->d_callbacks.begin(),
                                 this->d_callbacks.end(),
                                 [&](std::unique_ptr<base>& other)
                                 {
                                     return tmp.do_cmp(other.get());
                                 });
        this->d_callbacks.erase(it, this->d_callbacks.end());
        return *this;
    }

    //operador que realiza la llamada
    void operator()(Args... args)
    {
        for (auto& callback : this->d_callbacks)
        {
            callback->do_call(args...);
        }
    }
};
