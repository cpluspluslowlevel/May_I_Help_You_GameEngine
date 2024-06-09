#ifndef _MIHYCORE_DATASTRUCT_H_
#define _MIHYCORE_DATASTRUCT_H_

namespace MIHYCore{
    namespace DataStruct{

        template <typename Type>
        class Vector{
        private:

            Type* m_memory;
            int   m_capacity;
            int   m_size;

        public:
            Vector(int capacity = 10) : m_capacity(capacity), m_size(0){
                m_memory = new Type[m_capacity];
            }
            Vector(const Vector& other) : m_capacity(other.m_capacity), m_size(other.m_size) {
                m_memory = new Type[m_capacity];
                for (int i = 0; i < m_size; i++) {
                    m_memory[i] = other.m_memory[i];
                }
            }
            Vector(Vector&& other) noexcept : m_capacity(other.m_capacity), m_size(other.m_size), m_memory(other.m_memory) {
                other.m_capacity    = 0;
                other.m_size        = 0;
                other.m_memory      = nullptr;
            }
            ~Vector(){
                delete[] m_memory;
            }
            Vector& operator=(const Vector& other){

                if (this != &other) {
                    
                    delete[] m_memory;
                    
                    m_capacity = other.m_capacity;
                    m_size     = other.m_size;
                    m_memory   = new Type[m_capacity];
                    for (int i = 0; i < m_size; i++) {
                        m_memory[i] = other.m_memory[i];
                    }

                }

                return *this;

            }
            Vector& operator=(Vector&& other) noexcept {

                if (this != &other) {

                    delete[] m_memory;

                    m_capacity = other.m_capacity;
                    m_size     = other.m_size;
                    m_memory   = other.m_memory;

                    other.m_capacity    = 0;
                    other.m_size        = 0;
                    other.m_memory      = nullptr;

                }

                return *this;

            }

            void push_back(const Type& value){

                if(m_size == m_capacity){
                    increase_capacity();
                }

            }

            void increase_capacity()
            {

            }

        private:

            void calculate_next_capacity(int capacity)
            {

            }

        };

    }
}



#endif