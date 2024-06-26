#ifndef _MIHYCORE_DATASTRUCT_H_
#define _MIHYCORE_DATASTRUCT_H_

namespace MIHYCore{
    namespace DataStruct{


        /// @brief                      두 반복자 사이의 거리를 계산합니다.
        /// @tparam Iterator            반복자의 타입
        /// @param  begin               반복자의 시작
        /// @param  end                 반복자의 끝
        /// @return 두 반복자 사이의 거리
        template<typename Iterator>
        UInt64 mihyiterator_distance(Iterator begin, Iterator end){
            UInt64 distance{0};
            while(begin != end){
                ++begin;
                ++distance;
            }
            return distance;
        }

        /// @brief          동적 배열을 구현한 클래스입니다.
        /// @details        일정한 크기의 메모리를 할당하고 원소를 추가하다 메모리가 꽉 차면 더큰 메모리를 할당하고 기존의 원소를 복사하는 방식으로 작동합니다.
        ///                 메모리를 할당할 때 모든 메모리가 복사 또는 이동하는 작업이 수반되므로 빈번한 메모리 할당이 발생하지 않도록 주의해야 합니다. 크기가 예상되면 reserve_capacity를 사용하여 미리 큰 메모리를 할당하는 것이 좋습니다.
        /// @tparam Type    원소의 타입
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

            /// @brief              생성자
            /// @param capacity     초기 메모리의 크기 0을 입력하면 임의의 크기로 초기화됩니다.
            MIHYVector(UInt64 capacity) : m_capacity{capacity}, m_size{0}{
                if(m_capacity == 0){
                    m_capacity = 2;
                }
                m_memory = new Type[m_capacity];
            }

            /// @brief              생성자
            /// @param capacity     초기 메모리의 크기 0을 입력하면 임의의 크기로 초기화됩니다.
            /// @param list         초기화 리스트
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

            /// @brief          복사 생성자
            /// @param lvalue   복사 대상
            MIHYVector(const MIHYVector& lvalue) : m_capacity{lvalue.m_capacity}, m_size{lvalue.m_size}{
                m_memory = new Type[m_capacity];
                for (UInt64 i = 0; i < m_size; i++) {
                    m_memory[i] = lvalue.m_memory[i];
                }
            }

            /// @brief          이동 생성자
            /// @param rvalue   이동 대상
            MIHYVector(MIHYVector&& rvalue) noexcept : m_memory{rvalue.m_memory}, m_capacity{rvalue.m_capacity}, m_size{rvalue.m_size}{
                rvalue.m_capacity    = 0;
                rvalue.m_size        = 0;
                rvalue.m_memory      = nullptr;
            }

            /// @brief 소멸자
            ~MIHYVector(){
                delete[] m_memory;
            }

            /// @brief          복사 대입 연산자
            /// @param lvalue   복사 대상
            /// @return         스스로의 참조
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

            /// @brief          이동 대입 연산자
            /// @param rvalue   이동 대상 
            /// @return         스스로의 참조
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

            /// @brief          뒤에 원소를 추가합니다.
            /// @param lvalue   원소의 값
            void push_back(const Type& lvalue){

                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1);
                }

                m_memory[m_size++] = lvalue;

            }

            /// @brief          뒤에 원소를 추가합니다.
            /// @param rvalue   원소의 값
            void push_back(Type&& rvalue){

                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1);
                }

                m_memory[m_size++] = std::move(rvalue);

            }

            /// @brief          뒤에 원소를 추가합니다.
            /// @param list     추가할 원소의 초기화 리스트
            void push_back(std::initializer_list<Type> list){

                if(m_size + list.size() > m_capacity){
                    reserve_capacity(m_size + list.size());
                }

                for(auto&& e : list){
                    m_memory[m_size++] = std::move(e);
                }

            }

            /// @brief          뒤에 원소를 추가합니다.
            /// @param lvalue   추가할 원소에 대한 벡터
            void push_back(const MIHYVector& lvalue){

                if(m_size + lvalue.m_size > m_capacity){
                    reserve_capacity(m_size + lvalue.m_size);
                }

                for(const auto& e : lvalue){
                    m_memory[m_size++] = e;
                }

            }
            
            /// @brief          뒤에 원소를 추가합니다.
            /// @param rvalue   추가할 원소에 대한 벡터
            void push_back(MIHYVector&& rvalue){

                if(m_size + rvalue.m_size > m_capacity){
                    reserve_capacity(m_size + rvalue.m_size);
                }

                for(auto e : rvalue){
                    m_memory[m_size++] = std::move(e);
                }

                rvalue.m_memory     = nullptr;
                rvalue.m_size       = 0;
                rvalue.m_capacity   = 0;

            }

            /// @brief              뒤에 원소를 추가합니다.
            /// @tparam Iterator    반복자의 타입
            /// @param  begin       반복자의 시작
            /// @param  end         반복자의 끝
            template<typename Iterator>
            void push_back(Iterator begin, Iterator end){

                UInt64 distance{mihyiterator_distance(begin, end)};

                if(m_size + distance > m_capacity){
                    reserve_capacity(m_size + distance);
                }

                while(begin != end){
                    m_memory[m_size++] = *begin;
                    ++begin;
                }

            }


            /// @brief          앞에 원소를 추가합니다.
            /// @param lvalue   원소의 값
            void push_front(const Type& lvalue){
                push(0, lvalue);
            }

            /// @brief          앞에 원소를 추가합니다.
            /// @param rvalue   원소의 값
            void push_front(Type&& rvalue){
                push(0, std::move(rvalue));
            }

            /// @brief          앞에 원소를 추가합니다.
            /// @param list     원소의 초기화 리스트
            void push_front(std::initializer_list<Type> list){
                push(0, list);
            }

            /// @brief          앞에 원소를 추가합니다.
            /// @param lvalue   추가할 원소에 대한 백터
            void push_front(const MIHYVector& lvalue){
                push(0, lvalue);
            }

            /// @brief          앞에 원소를 추가합니다.
            /// @param rvalue   추가할 원소에 대한 벡터
            void push_front(MIHYVector&& rvalue){
                push(0, std::move(rvalue));
            }

            /// @brief              앞에 원소를 추가합니다.
            /// @tparam Iterator    반복자 타입
            /// @param  begin       시작 반복자
            /// @param  end         끝 반복자
            template<typename Iterator>
            void push_front(Iterator begin, Iterator end){
                push(0, begin, end);
            }

            /// @brief          원소를 추가합니다.
            /// @param index    원소가 들어갈 인덱스
            /// @param lvalue   원소의 값
            void push(UInt64 index, const Type& lvalue){

                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1, 1, index);
                }else{
                    shift_right_element(index, 1);
                }

                m_memory[index] = lvalue;
                ++m_size;

            }

            /// @brief          원소를 추가합니다.
            /// @param index    원소가 들어갈 인덱스
            /// @param rvalue   원소의 값
            void push(UInt64 index, Type&& rvalue){

                if(m_size == m_capacity){
                    reserve_capacity(m_size + 1, 1, index);
                }else{
                    shift_right_element(index, 1);
                }

                m_memory[index] = std::move(rvalue);
                ++m_size;

            }

            /// @brief          원소를 추가합니다.
            /// @param index    원소가 들어갈 인덱스
            /// @param list     추가할 원소의 초기화 리스트
            void push(UInt64 index, std::initializer_list<Type> list){

                if(m_size + list.size() > m_capacity){
                    reserve_capacity(m_size + list.size(), list.size(), index);
                }else{
                    shift_right_element(index, list.size());
                }

                UInt64 push_index{index};
                for(auto e : list){
                    m_memory[push_index++] = std::move(e);
                }

                m_size += list.size();

            }

            /// @brief          원소를 추가합니다.
            /// @param index    원소가 들어갈 인덱스
            /// @param lvalue   추가할 원소에 대한 벡터
            void push(UInt64 index, const MIHYVector& lvalue){

                if(m_size + lvalue.m_size > m_capacity){
                    reserve_capacity(m_size + lvalue.m_size, lvalue.m_size, index);
                }else{
                    shift_right_element(index, lvalue.m_size);
                }

                UInt64 push_index{index};
                for(const auto& e : lvalue){
                    m_memory[push_index++] = e;
                }

                m_size += lvalue.m_size;

            }

            /// @brief          원소를 추가합니다.
            /// @param index    원소가 들어갈 인덱스
            /// @param lvalue   추가할 원소에 대한 벡터
            void push(UInt64 index, MIHYVector&& rvalue){

                if(m_size + rvalue.m_size > m_capacity){
                    reserve_capacity(m_size + rvalue.m_size, rvalue.m_size, index);
                }else{
                    shift_right_element(index, rvalue.m_size);
                }

                UInt64 push_index{index};
                for(auto&& e : rvalue){
                    m_memory[push_index++] = std::move(e);
                }

                m_size += rvalue.m_size;

                rvalue.m_memory   = nullptr;
                rvalue.m_size     = 0;
                rvalue.m_capacity = 0;

            }

            /// @brief              원소를 추가합니다.
            /// @tparam Iterator    반복자 타입
            /// @param  index       원소가 들어갈 인덱스
            /// @param  begin       반복자의 시작
            /// @param  end         반복자의 끝
            template<typename Iterator>
            void push(UInt64 index, Iterator begin, Iterator end){

                UInt64 distance{mihyiterator_distance(begin, end)};

                if(m_size + distance > m_capacity){
                    reserve_capacity(m_size + distance, distance, index);
                }else{
                    shift_right_element(index, distance);
                }

                UInt64 push_index{index};
                while(begin != end){
                    m_memory[push_index++] = *begin;
                    ++begin;
                }

                m_size += distance;

            }

            /// @brief 마지막 원소를 제거합니다.
            void pop_back(){
                if(m_size > 0){
                    --m_size;
                }
            }

            void pop_front(){
                if(m_size > 0){
                    shift_left_element(0, 1);
                    --m_size;
                }
            }

            void pop(UInt64 index){
                if(m_size == 0){
                    return;
                }else if(index == m_size - 1){
                    --m_size;
                    return;
                }else{
                    shift_left_element(index + 1, 1);
                    --m_size;
                }
            }

            /// @brief 모든 원소를 제거합니다.
            void clear(){
                m_size = 0;
            }

            /// @brief                              메모리를 할당합니다.
            /// @details                            approximated_capacity수치를 기반으로 적당한 크기의 메모리를 할당합니다. approximated_capacity보다 크거나 같은 크기의 메모리가 할당되나 정확한 크기는 아닙니다. 
            ///                                     만약 approximated_capacity가 현재 메모리의 크기보다 작다면 아무런 작업을 하지 않습니다.
            /// @param approximated_capacity        원하는 메모리의 대략적인 크기
            /// @param copy_offset                  복사할 원소의 오프셋. 오프셋으로 인해 원소가 메모리 밖에 복사되는지 감시하지 않습니다. 적합한 값을 사용하세요.
            /// @param copy_offset_start_index      copy_offset를 적용할 시작 인덱스
            void reserve_capacity(UInt64 approximated_capacity, UInt64 copy_offset = 0, UInt64 copy_offset_start_index = 0)
            {

                if(approximated_capacity <= m_capacity){
                    return;
                }

                while(m_capacity < approximated_capacity){
                    expand_capacity();
                }

                auto temp_memory{m_memory};
                m_memory = new Type[m_capacity];
                for(UInt64 i = 0; i < copy_offset_start_index; ++i){
                    m_memory[i] = temp_memory[i];
                }
                for(UInt64 i = copy_offset_start_index; i < m_size; ++i){
                    m_memory[i + copy_offset] = temp_memory[i];
                }

                delete[] temp_memory;

            }

            /// @brief          원소의 개수를 조정합니다. 기존에 생성된 원소는 유지됩니다.
            /// @param size     원하는 원소의 개수
            void resize(UInt64 size)
            {
                if(size > m_capacity){
                    reserve_capacity(size);
                }
                m_size = size;
            }



            /// @brief      컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return     첫 요소를 가리키는 반복자.
            Iterator begin(){
                return m_memory;
            }

            /// @brief      컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return     첫 요소를 가리키는 반복자.
            Const_Iterator begin() const{
                return m_memory;
            }

            /// @brief      반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return     반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Iterator end(){
                return m_memory + m_size;
            }

            /// @brief      반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return     반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Const_Iterator end() const{
                return m_memory + m_size;
            }

            /// @brief      컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return     첫 요소를 가리키는 반복자.
            Const_Iterator cbegin() const{
                return m_memory;
            }

            /// @brief      반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return     반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Const_Iterator cend() const{
                return m_memory + m_size;
            }

            /// @brief      역순으로 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return     첫 요소를 가리키는 반복자.
            Reverse_Iterator rbegin(){
                return Reverse_Iterator{m_memory + m_size - 1};
            }

            /// @brief      반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return     반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Reverse_Iterator rend(){
                return Reverse_Iterator{m_memory - 1};
            }

            /// @brief      역순으로 컨테이너의 첫번째 요소를 가리키는 반복자를 반환합니다.
            /// @return     첫 요소를 가리키는 반복자.
            Const_Reverse_Iterator crbegin() const{
                return Const_Reverse_Iterator{m_memory + m_size - 1};
            }

            /// @brief      반복자가 범위 밖을 넘어갔는지 검사하는 반복자를 반환합니다.
            /// @return     반복자가 범위 밖을 나갔는지를 나타내는 반복자
            Const_Reverse_Iterator crend() const{
                return Const_Reverse_Iterator{m_memory - 1};
            }



            /// @brief      현재 메모리를 반환합니다. 벡터의 크기가 변경되면 메모리가 해제될 수 있습니다.
            /// @return     메모리의 주소
            Type* get_memory(){
                return m_memory;
            }

            /// @brief      현재 메모리의 보관 가능한 원소의 개수를 반환합니다.
            /// @return     m_capacity 현재 메모리의 보관 가능한 원소의 개수
            UInt64 get_capacity() const{
                return m_capacity;
            }

            /// @brief      현재 원소의 개수를 반환합니다.
            /// @return     현재 원소의 개수
            UInt64 get_size() const{
                return m_size;
            }





            /// @brief          배열 형식으로 원소에 접근합니다.
            /// @param index    배열 인덱스
            /// @return         원소에 대한 레퍼런스
            Type& operator[](UInt64 index){
                return m_memory[index];
            }

            /// @brief          배열 형식으로 원소에 접근합니다.
            /// @param index    배열 인덱스
            /// @return         원소에 대한 레퍼런스
            const Type& operator[](UInt64 index) const{
                return m_memory[index];
            }


        private:

            /// @brief 현재 메모리의 크기를 확장합니다.
            void expand_capacity(){
                m_capacity = m_capacity * 2 + 1;
            }

            /// @brief                  원소들을 오른쪽으로 일정 거리 이동시킵니다.
            /// @param start_index      이동을 시작할 인덱스
            /// @param distance         이동할 거리
            void shift_right_element(UInt64 start_index, UInt64 distance){
                
                //m_size - 1이 언더플로우가 일어나기 때문에 예외처리 합니다.
                if(m_size == 0){
                    return;
                }

                UInt64 i{m_size - 1};
                while(true){
                    m_memory[i + distance] = std::move(m_memory[i]);
                    if(i == start_index){
                        break;
                    }
                    --i;
                }

            }


            /// @brief                  원소들을 왼쪽으로 일정 거리 이동시킵니다.
            /// @param start_index      이동을 시작할 인덱스
            /// @param distance         이동할 거리
            void shift_left_element(UInt64 start_index, UInt64 distance){

                //왼쪽으로 밀면서 메모리에서 벗어나 소실되는 원소의 개수를 계산합니다.
                UInt64 release_element_number{0};
                if(start_index < distance){
                    release_element_number = distance - start_index;
                }
                

                UInt64 index{start_index + release_element_number};
                while(index < m_size){
                    m_memory[index - distance] = std::move(m_memory[index]);
                    ++index;
                }

            }


        };


        /// @brief          벡터의 역방향 반복자입니다.
        /// @tparam Type    벡터의 원소 타입
        template<typename Type>
        class MIHYVector<Type>::RIterator{
        private:

            Type* m_pointer;

        public:

            /// @brief          복사 생성자입니다.
            /// @param lvalue   복사 대상
            RIterator(const RIterator& lvalue) : m_pointer{lvalue.m_pointer}{}

            /// @brief          이동 생성자입니다.
            /// @param rvalue   이동 대상
            RIterator(RIterator&& rvalue) noexcept : m_pointer{rvalue.m_pointer}{}

            /// @brief          복사 대입 연산자입니다.
            /// @param lvalue   복사 대상
            /// @return         스스로의 참조
            RIterator& operator=(const RIterator& lvalue){
                m_pointer = lvalue.m_pointer;
                return *this;
            }

            /// @brief          이동 대입 연산자입니다.
            /// @param rvalue   이동 대상
            /// @return         스스로의 참조
            RIterator& operator=(RIterator&& rvalue) noexcept{
                m_pointer = rvalue.m_pointer;
                return *this;
            }

            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            Type* operator->(){
                return m_pointer;
            }

            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            const Type* operator->() const{
                return m_pointer;
            }

            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            Type& operator*(){
                return *m_pointer;
            }

            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            const Type& operator*() const{
                return *m_pointer;
            }

            /// @brief      다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return     스스로의 참조
            RIterator& operator++(){
                --m_pointer;
                return *this;
            }

            /// @brief      다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param      후위 증가 연산자를 구분하기 위한 더미 인자
            /// @return     기존 원소를 가리키는 반복자
            RIterator operator++(int){
                RIterator temp{*this};
                --m_pointer;
                return temp;
            }

            /// @brief      이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return     스스로의 참조
            RIterator& operator--(){
                ++m_pointer;
                return *this;
            }

            /// @brief      이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param      후위 감소 연산자를 구분하기 위한 더미 인자
            /// @return     기존 원소를 가리키는 반복자
            RIterator operator--(int){
                RIterator temp{*this};
                ++m_pointer;
                return temp;
            }

            /// @brief              다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param  offset      이동할 원소의 개수
            /// @return             스스로의 참조
            RIterator& operator+=(UInt64 offset){
                m_pointer -= offset;
                return *this;
            }

            /// @brief          다음 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         offset만큼 이동한 위치의 새로운 반복자
            RIterator operator+(UInt64 offset) const{
                return RIterator{m_pointer - offset};
            }

            /// @brief          이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         스스로의 참조
            RIterator& operator-=(UInt64 offset){
                m_pointer += offset;
                return *this;
            }

            /// @brief          이전 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         offset만큼 이동한 위치의 새로운 반복자
            RIterator operator-(UInt64 offset) const{
                return RIterator{m_pointer + offset};
            }

            /// @brief          두 반복자가 같은지 비교합니다.
            /// @param other    비교할 반복자
            /// @return         같으면 true, 다르면 false
            bool operator==(const RIterator& other) const{
                return m_pointer == other.m_pointer;
            }

            /// @brief          두 반복자가 다른지 비교합니다.
            /// @param other    비교할 반복자
            /// @return         다르면 true, 같으면 false
            bool operator!=(const RIterator& other) const{
                return m_pointer != other.m_pointer;
            }

        private:

            /// @brief              내부적으로 사용하는 생성자 입니다. 벡터의 메모리 주소를 받아 저장합니다.
            /// @param pointer      벡터의 메모리
            RIterator(Type* pointer) : m_pointer{pointer}{}

            friend class MIHYVector<Type>;

        };

        /// @brief          벡터의 역방향 반복자입니다.
        /// @tparam Type    벡터의 원소 타입
        template<typename Type>
        class MIHYVector<Type>::CRIterator{
        private:

            Type* m_pointer;

        public:

            /// @brief          복사 생성자입니다.
            /// @param lvalue   복사 대상
            CRIterator(const CRIterator& lvalue) : m_pointer{lvalue.m_pointer}{}

            /// @brief          이동 생성자입니다.
            /// @param rvalue   이동 대상
            CRIterator(CRIterator&& rvalue) noexcept : m_pointer{rvalue.m_pointer}{}

            /// @brief          복사 대입 연산자입니다.
            /// @param lvalue   복사 대상
            /// @return         스스로의 참조
            CRIterator& operator=(const CRIterator& lvalue){
                m_pointer = lvalue.m_pointer;
                return *this;
            }

            /// @brief          이동 대입 연산자입니다.
            /// @param rvalue   이동 대상
            /// @return         스스로의 참조
            CRIterator& operator=(CRIterator&& rvalue) noexcept{
                m_pointer = rvalue.m_pointer;
                return *this;
            }


            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            const Type* operator->() const{
                return m_pointer;
            }

            /// @brief      역참조 연산자입니다.
            /// @return     역참조된 값
            const Type& operator*() const{
                return *m_pointer;
            }

            /// @brief      다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return     스스로의 참조
            CRIterator& operator++(){
                --m_pointer;
                return *this;
            }

            /// @brief      다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param      후위 증가 연산자를 구분하기 위한 더미 인자
            /// @return     기존 원소를 가리키는 반복자
            CRIterator operator++(int){
                CRIterator temp{*this};
                --m_pointer;
                return temp;
            }

            /// @brief      이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @return     스스로의 참조
            CRIterator& operator--(){
                ++m_pointer;
                return *this;
            }

            /// @brief      이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param      후위 감소 연산자를 구분하기 위한 더미 인자
            /// @return     기존 원소를 가리키는 반복자
            CRIterator operator--(int){
                CRIterator temp{*this};
                ++m_pointer;
                return temp;
            }

            /// @brief          다음 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         스스로의 참조
            CRIterator& operator+=(UInt64 offset){
                m_pointer -= offset;
                return *this;
            }

            /// @brief          다음 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         offset만큼 이동한 위치의 새로운 반복자
            CRIterator operator+(UInt64 offset) const{
                return CRIterator{m_pointer - offset};
            }

            /// @brief          이전 원소로 이동합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         스스로의 참조
            CRIterator& operator-=(UInt64 offset){
                m_pointer += offset;
                return *this;
            }

            /// @brief          이전 원소로 이동한 반복자를 반환합니다. 역방향으로 이동합니다.
            /// @param offset   이동할 원소의 개수
            /// @return         offset만큼 이동한 위치의 새로운 반복자
            CRIterator operator-(UInt64 offset) const{
                return CRIterator{m_pointer + offset};
            }

            /// @brief          두 반복자가 같은지 비교합니다.
            /// @param other    비교할 반복자
            /// @return         같으면 true, 다르면 false
            bool operator==(const CRIterator& other) const{
                return m_pointer == other.m_pointer;
            }

            /// @brief          두 반복자가 다른지 비교합니다.
            /// @param other    비교할 반복자
            /// @return         다르면 true, 같으면 false
            bool operator!=(const CRIterator& other) const{
                return m_pointer != other.m_pointer;
            }

        private:

            /// @brief 내부적으로 사용하는 생성자 입니다. 벡터의 메모리 주소를 받아 저장합니다.
            /// @param pointer 벡터의 메모리
            CRIterator(Type* pointer) : m_pointer{pointer}{}

            friend class MIHYVector<Type>;

        };



        template<typename Type>
        class MIHYList{
        private:
        public:
        };






        //Unit test
        MIHYCORE_API void mihyvector_unittest();
        MIHYCORE_API void mihylist_unittest();





        /// @brief              Foreach에서 역방향 반복자를 사용하기 위한 어뎁터 클래스입니다.
        /// @tparam Container   컨테이너 타입
        template<typename Container>
        class MIHYIterator_ForEach_Reverse{
        private:

            Container& m_container;

        public:
            /// @brief              생성자
            /// @param container    반복자를 사용할 컨테이너
            MIHYIterator_ForEach_Reverse(Container& container) : m_container{container}{}

            /// @brief   역방향 반복자의 시작을 반환합니다.
            /// @return  역방향 반복자의 시작
            Container::Reverse_Iterator begin(){
                return m_container.rbegin();
            }

            /// @brief   역방향 반복자의 끝을 반환합니다.
            /// @return  역방향 반복자의 끝
            Container::Reverse_Iterator end(){
                return m_container.rend();
            }

        };


    }
}



#endif