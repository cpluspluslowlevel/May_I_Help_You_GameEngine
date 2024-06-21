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
        public:

            class RIterator;
            class CRIterator;

            using Iterator                  = Type*;
            using Const_Iterator            = const Type*;
            using Reverse_Iterator          = RIterator;
            using Const_Reverse_Iterator    = const CRIterator;

        private:

            Type*       m_memory;
            UInt64      m_capacity;
            UInt64      m_size;

        public:

            /// @brief 생성자
            /// @param capacity 초기 메모리의 크기 0을 입력하면 임의의 크기로 초기화됩니다.
            MIHYVector(UInt64 capacity) : m_capacity{capacity}, m_size{0}{
                if(m_capacity == 0){
                    m_capacity = 2;
                }
                m_memory = new Type[m_capacity];
            }

            /// @brief 생성자
            /// @param capacity 초기 메모리의 크기 0을 입력하면 임의의 크기로 초기화됩니다.
            /// @param list 초기화 리스트
            MIHYVector(UInt64 capacity, std::initializer_list<Type> list) : m_memory{nullptr}, m_capacity{capacity}, m_size{0}{

                if(m_capacity == 0){
                    m_capacity = 2;
                }
                
                if(m_capacity < list.size()){
                    reserve_capacity(list.size());
                }else{
                    m_memory = new Type[m_capacity];
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
            MIHYVector(MIHYVector&& rvalue) noexcept : m_memory{rvalue.m_memory}, m_capacity{rvalue.m_capacity}, m_size{rvalue.m_size}{
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

                //메모리가 부족하면 늘립니다.
                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1);
                }

                m_memory[m_size++] = lvalue;

            }

            /// @brief 뒤에 원소를 추가합니다.
            /// @param value 이동할 데이터
            void push_back(Type&& rvalue){

                //메모리가 부족하면 늘립니다.
                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1);
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

            void push_front(const Type& lvalue){

                //메모리가 부족하면 늘립니다.
                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1);
                }

                for(UInt64 i = m_size; i > 0; --i){
                    m_memory[i] = m_memory[i - 1];
                }

                m_memory[0] = lvalue;
                ++m_size;

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

            /// @brief 메모리를 미리 할당합니다.
            /// @details approximated_capacity수치를 기반으로 적당한 크기의 메모리를 미리 할당합니다. approximated_capacity보다 큰 크기의 메모리가 할당되나 정확한 크기는 아닙니다. 
            ///          만약 approximated_capacity가 현재 메모리의 크기보다 작다면 아무런 작업을 하지 않습니다.
            /// @param approximated_capacity 원하는 메모리의 대략적인 크기
            void reserve_capacity(UInt64 approximated_capacity)
            {

                if(approximated_capacity <= m_capacity){
                    return;
                }

                //특정 벡터가 다른 벡터에 본인의 데이터를 전해주면(rvalue) 본인은 빈 벡터가 됩니다.
                //그 후 빈 벡터를 다시 사용하려고 할 때 무한 루프가 발생하지 않도록 최소 크기로 지정합니다.
                //m_memory가 nullptr로 남아있긴 하지만 delete는 null safe하므로 문제가 되지 않습니다.
                if(m_capacity == 0){
                    m_capacity = 2;
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



            /// @brief 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return 첫 요소를 가리키는 반복자.
            Iterator begin(){
                return m_memory;
            }

            /// @brief 반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return 반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Iterator end(){
                return m_memory + m_size;
            }

            /// @brief 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return 첫 요소를 가리키는 반복자.
            Const_Iterator cbegin() const{
                return m_memory;
            }

            /// @brief 반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return 반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Const_Iterator cend() const{
                return m_memory + m_size;
            }

            /// @brief 역순으로 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return 첫 요소를 가리키는 반복자.
            Reverse_Iterator rbegin(){
                return Reverse_Iterator{m_memory + m_size - 1};
            }

            /// @brief 반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return 반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Reverse_Iterator rend(){
                return Reverse_Iterator{m_memory - 1};
            }

            /// @brief 역순으로 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return 첫 요소를 가리키는 반복자.
            Const_Reverse_Iterator crbegin() const{
                return Const_Reverse_Iterator{m_memory + m_size - 1};
            }

            /// @brief 반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return 반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Const_Reverse_Iterator crend() const{
                return Const_Reverse_Iterator{m_memory - 1};
            }



            /// @brief 현재 메모리를 반환합니다. 벡터의 크기가 변경되면 메모리가 해제될 수 있습니다.
            /// @return 메모리의 주소
            Type* get_memory(){
                return m_memory;
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
                m_capacity = m_capacity * 2;
            }

        };


        /// @brief 벡터의 역방향 반복자입니다.
        /// @tparam Type 벡터의 원소 타입
        template<typename Type>
        class MIHYVector<Type>::RIterator{
        private:

            Type* m_pointer;

        public:

            /// @brief 복사 생성자입니다.
            /// @param lvalue 복사 대상
            RIterator(const RIterator& lvalue) : m_pointer{lvalue.m_pointer}{}

            /// @brief 이동 생성자입니다.
            /// @param rvalue 
            RIterator(RIterator&& rvalue) noexcept : m_pointer{rvalue.m_pointer}{}

            /// @brief 복사 대입 연산자입니다.
            /// @param lvalue 복사 대상
            /// @return 스스로의 참조
            RIterator& operator=(const RIterator& lvalue){
                m_pointer = lvalue.m_pointer;
                return *this;
            }

            /// @brief 이동 대입 연산자입니다.
            /// @param rvalue 이동 대상
            /// @return 스스로의 참조
            RIterator& operator=(RIterator&& rvalue) noexcept{
                m_pointer = rvalue.m_pointer;
                return *this;
            }

            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            Type* operator->(){
                return m_pointer;
            }

            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            const Type* operator->() const{
                return m_pointer;
            }

            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            Type& operator*(){
                return *m_pointer;
            }

            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            const Type& operator*() const{
                return *m_pointer;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return 스스로의 참조
            RIterator& operator++(){
                --m_pointer;
                return *this;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param 후위 증가 연산자를 구분하기 위한 더미 인자
            /// @return 기존 원소를 가리키는 반복자
            RIterator operator++(int){
                RIterator temp{*this};
                --m_pointer;
                return temp;
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return 스스로의 참조
            RIterator& operator--(){
                ++m_pointer;
                return *this;
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param 후위 감소 연산자를 구분하기 위한 더미 인자
            /// @return 기존 원소를 가리키는 반복자
            RIterator operator--(int){
                RIterator temp{*this};
                ++m_pointer;
                return temp;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return 스스로의 참조
            RIterator& operator+=(UInt64 offset){
                m_pointer -= offset;
                return *this;
            }

            /// @brief 다음 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return offset만큼 이동한 위치의 새로운 반복자
            RIterator operator+(UInt64 offset) const{
                return RIterator{m_pointer - offset};
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return 스스로의 참조
            RIterator& operator-=(UInt64 offset){
                m_pointer += offset;
                return *this;
            }

            /// @brief 이전 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return offset만큼 이동한 위치의 새로운 반복자
            RIterator operator-(UInt64 offset) const{
                return RIterator{m_pointer + offset};
            }

            bool operator==(const RIterator& other) const{
                return m_pointer == other.m_pointer;
            }

            bool operator!=(const RIterator& other) const{
                return m_pointer != other.m_pointer;
            }

        private:

            /// @brief 내부적으로 사용하는 생성자 입니다. 벡터의 메모리 주소를 받아 저장합니다.
            /// @param pointer 벡터의 메모리
            RIterator(Type* pointer) : m_pointer{pointer}{}

            friend class MIHYVector<Type>;

        };

        /// @brief 벡터의 역방향 반복자입니다.
        /// @tparam Type 벡터의 원소 타입
        template<typename Type>
        class MIHYVector<Type>::CRIterator{
        private:

            Type* m_pointer;

        public:

            /// @brief 복사 생성자입니다.
            /// @param lvalue 복사 대상
            CRIterator(const CRIterator& lvalue) : m_pointer{lvalue.m_pointer}{}

            /// @brief 이동 생성자입니다.
            /// @param rvalue 
            CRIterator(CRIterator&& rvalue) noexcept : m_pointer{rvalue.m_pointer}{}

            /// @brief 복사 대입 연산자입니다.
            /// @param lvalue 복사 대상
            /// @return 스스로의 참조
            CRIterator& operator=(const CRIterator& lvalue){
                m_pointer = lvalue.m_pointer;
                return *this;
            }

            /// @brief 이동 대입 연산자입니다.
            /// @param rvalue 이동 대상
            /// @return 스스로의 참조
            CRIterator& operator=(CRIterator&& rvalue) noexcept{
                m_pointer = rvalue.m_pointer;
                return *this;
            }


            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            const Type* operator->() const{
                return m_pointer;
            }

            /// @brief 역참조 연산자입니다.
            /// @return 역참조된 값
            const Type& operator*() const{
                return *m_pointer;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return 스스로의 참조
            CRIterator& operator++(){
                --m_pointer;
                return *this;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param 후위 증가 연산자를 구분하기 위한 더미 인자
            /// @return 기존 원소를 가리키는 반복자
            CRIterator operator++(int){
                CRIterator temp{*this};
                --m_pointer;
                return temp;
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return 스스로의 참조
            CRIterator& operator--(){
                ++m_pointer;
                return *this;
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param 후위 감소 연산자를 구분하기 위한 더미 인자
            /// @return 기존 원소를 가리키는 반복자
            CRIterator operator--(int){
                CRIterator temp{*this};
                ++m_pointer;
                return temp;
            }

            /// @brief 다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return 스스로의 참조
            CRIterator& operator+=(UInt64 offset){
                m_pointer -= offset;
                return *this;
            }

            /// @brief 다음 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return offset만큼 이동한 위치의 새로운 반복자
            CRIterator operator+(UInt64 offset) const{
                return CRIterator{m_pointer - offset};
            }

            /// @brief 이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return 스스로의 참조
            CRIterator& operator-=(UInt64 offset){
                m_pointer += offset;
                return *this;
            }

            /// @brief 이전 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset 이동할 원소의 개수
            /// @return offset만큼 이동한 위치의 새로운 반복자
            CRIterator operator-(UInt64 offset) const{
                return CRIterator{m_pointer + offset};
            }

            bool operator==(const CRIterator& other) const{
                return m_pointer == other.m_pointer;
            }

            bool operator!=(const CRIterator& other) const{
                return m_pointer != other.m_pointer;
            }

        private:

            /// @brief 내부적으로 사용하는 생성자 입니다. 벡터의 메모리 주소를 받아 저장합니다.
            /// @param pointer 벡터의 메모리
            CRIterator(Type* pointer) : m_pointer{pointer}{}

            friend class MIHYVector<Type>;

        };

        //Unit test
        MIHYCORE_API std::string MIHYVector_UnitTest();

        template<typename Container>
        class MIHYIterator_ForEach_Reverse{
        private:

            Container& m_container;

        public:
            MIHYIterator_ForEach_Reverse(Container& container) : m_container{container}{}

            Container::Reverse_Iterator begin(){
                return m_container.rbegin();
            }

            Container::Reverse_Iterator end(){
                return m_container.rend();
            }

        };

    }
}



#endif