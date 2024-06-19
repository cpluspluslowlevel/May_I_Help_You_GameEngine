#ifndef _MIHYCORE_DATASTRUCT_H_
#define _MIHYCORE_DATASTRUCT_H_

namespace MIHYCore{
    namespace DataStruct{


        /// @brief 동적 배열을 구현한 클래스입니다.
        /// @tparam Type 원소의 타입
        /// @details 일정한 크기의 메모리를 할당하고 원소를 추가하다 메모리가 꽉 차면 더큰 메모리를 할당하고 기존의 원소를 복사하는 방식으로 작동합니다.
        ///          메모리를 할당할 때 모든 메모리가 복사 또는 이동하는 작업이 수반되므로 빈번한 메모리 할당이 발생하지 않도록 주의해야 합니다. 크기가 예상되면 reserve_capacity를 사용하여 미리 큰 메모리를 할당하는 것이 좋습니다.
        template <typename Type>
        class MIHYVector{
        private:

            Type*       m_memory;
            UInt64      m_capacity;
            UInt64      m_size;

        public:

            /// @brief 생성자
            /// @param capacity 초기 메모리의 크기 
            MIHYVector(UInt64 capacity) : m_capacity{capacity}, m_size{0}{
                m_memory = new Type[m_capacity];
            }

            /// @brief 생성자
            /// @param capacity 초기 메모리의 크기
            /// @param list 초기화 리스트
            MIHYVector(UInt64 capacity, std::initializer_list<Type> list) : m_capacity{capacity}, m_size{0}{
                
                if(m_capacity < list.size()){
                    reserve_capacity(list.size());
                }

                auto iter_end{list.end()};
                for(auto iter{list.begin()}; iter != iter_end; ++iter){
                    m_memory[m_size++] = *iter;
                }
                m_size = list.size();

            }

            /// @brief 복사 생성자
            /// @param lvalue 복사 대상
            MIHYVector(const MIHYVector& lvalue) : m_capacity{lvalue.m_capacity}, m_size{lvalue.m_size}{
                m_memory = new Type[m_capacity];
                for (UInt64 i = 0; i < m_size; i++) {
                    m_memory[i] = lvalue.m_memory[i];
                }
            }

            /// @brief 이동 생성자
            /// @param rvalue 이동 대상
            MIHYVector(MIHYVector&& rvalue) noexcept : m_capacity{rvalue.m_capacity}, m_size{rvalue.m_size}, m_memory{rvalue.m_memory}{
                rvalue.m_capacity    = 0;
                rvalue.m_size        = 0;
                rvalue.m_memory      = nullptr;
            }

            /// @brief 소멸자
            ~MIHYVector(){
                delete[] m_memory;
            }

            /// @brief 복사 대입 연산자
            /// @param lvalue 복사 대상
            /// @return 스스로의 참조
            MIHYVector& operator=(const MIHYVector& lvalue){

                if (this != &lvalue) {
                    
                    delete[] m_memory;
                    
                    m_capacity = lvalue.m_capacity;
                    m_size     = lvalue.m_size;
                    m_memory   = new Type[m_capacity];
                    for (UInt64 i = 0; i < m_size; i++) {
                        m_memory[i] = lvalue.m_memory[i];
                    }

                }

                return *this;

            }

            /// @brief 이동 대입 연산자
            /// @param rvalue 이동 대상 
            /// @return 스스로의 참조
            MIHYVector& operator=(MIHYVector&& rvalue) noexcept{

                if (this != &rvalue) {

                    delete[] m_memory;

                    m_capacity = rvalue.m_capacity;
                    m_size     = rvalue.m_size;
                    m_memory   = rvalue.m_memory;

                    rvalue.m_capacity    = 0;
                    rvalue.m_size        = 0;
                    rvalue.m_memory      = nullptr;

                }

                return *this;

            }

            /// @brief 뒤에 원소를 추가합니다.
            /// @param lvalue 복사할 데이터
            void push_back(const Type& lvalue){

                if(m_size == m_capacity){
                    expand_capacity();
                }

                m_memory[m_size++] = lvalue;

            }

            /// @brief 뒤에 원소를 추가합니다.
            /// @param value 이동할 데이터
            void push_back(Type&& rvalue){

                if(m_size == m_capacity){
                    expand_capacity();
                }

                m_memory[m_size++] = std::move(rvalue);

            }

            /// @brief 뒤에 원소를 추가합니다.
            /// @param list 추가할 원소의 초기화 리스트
            void push_back(std::initializer_list<Type> list){

                //메모리가 부족하면 늘립니다.
                if(m_size + list.size() > m_capacity){
                    reserve_capacity(m_size + list.size());
                }

                //모든 원소를 복사합니다.
                auto iter_end{list.end()};
                for(auto iter{list.begin()}; iter != iter_end; ++iter){
                    m_memory[m_size++] = *iter;
                }

            }

            /// @brief 마지막 원소를 제거합니다.
            void pop_back(){
                if(m_size > 0){
                    --m_size;
                }
            }

            /// @brief 모든 원소를 제거합니다.
            void clear(){
                m_size = 0;
            }

            /// @brief 현재 메모리의 보관 가능한 원소의 개수를 반환합니다.
            /// @return m_capacity 현재 메모리의 보관 가능한 원소의 개수
            UInt64 get_capacity() const{
                return m_capacity;
            }

            /// @brief 현재 원소의 개수를 반환합니다.
            /// @return 현재 원소의 개수
            UInt64 get_size() const{
                return m_size;
            }

            /// @brief 메모리를 미리 할당합니다.
            /// @details approximated_capacity수치를 기반으로 적당한 크기의 메모리를 미리 할당합니다. approximated_capacity보다 큰 크기의 메모리가 할당되나 정확한 크기는 아닙니다. 
            ///          만약 approximated_capacity가 현재 메모리의 크기보다 작다면 아무런 작업을 하지 않습니다.
            /// @param approximated_capacity 원하는 메모리의 대략적인 크기
            void reserve_capacity(UInt64 approximated_capacity)
            {

                if(approximated_capacity <= m_capacity){
                    return;
                }

                while(m_capacity < approximated_capacity){
                    expand_capacity();
                }

                auto temp_memory{m_memory};
                m_memory = new Type[m_capacity];
                for(UInt64 i = 0; i < m_size; ++i){
                    m_memory[i] = temp_memory[i];
                }

                delete[] temp_memory;

            }

            /// @brief 원소의 개수를 조정합니다. 기존에 생성된 원소는 유지됩니다.
            /// @param size 원하는 원소의 개수
            void resize(UInt64 size)
            {

                if(size > m_capacity){
                    reserve_capacity(size);
                }

                m_size = size;

            }

            /// @brief 배열 형식으로 원소에 접근합니다.
            /// @param index 배열 인덱스
            /// @return 원소에 대한 레퍼런스
            Type& operator[](UInt64 index){
                return m_memory[index];
            }

            /// @brief 배열 형식으로 원소에 접근합니다.
            /// @param index 배열 인덱스
            /// @return 원소에 대한 레퍼런스
            const Type& operator[](UInt64 index) const{
                return m_memory[index];
            }


        private:

            /// @brief 현재 메모리의 크기를 확장합니다.
            void expand_capacity(){
                reserve_capacity(m_capacity * 2);
            }

        };

        //Unit test
        MIHYCORE_API std::string MIHYVector_UnitTest();

    }
}



#endif