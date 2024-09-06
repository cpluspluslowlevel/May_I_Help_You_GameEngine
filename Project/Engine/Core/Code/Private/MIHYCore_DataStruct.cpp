#include "MIHYCore_PCH.h"
#include "MIHYCore_DataStruct.h"

#include <list>

namespace MIHYCore{
    namespace DataStruct{

        

    void mihyvector_unittest()
    {
        
#define VECTOR_PRINT(v) std::cout << "Capacity: " << v.get_capacity() << std::endl; for(UInt32 i = 0; i < v.get_size(); ++i) std::cout << v[i] << " "; std::cout << std::endl;
        using V = MIHYVector<Int32>;

        {//get_capacity
            V v{2};
            assert(v.get_capacity() == 2);
        }

        {//get_size
            V v{2, {0, 1, 2}};
            assert(v.get_size() == 3);
        }

        {//clear
            V v{2, {0, 1, 2}};
            assert(v.get_size() == 3);
            v.clear();
            assert(v.get_size() == 0);
        }

        {//operator[]
            V v{2, {0, 1, 2}};
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        //생성자
        {   V v{10};   assert(v.get_capacity() == 10);  }

        {//생성자(초기화 리스트)
            V v{5, {0, 1, 2}};
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };

        {//생성자(초기화 리스트, 시작 크기보다 많은 원소가 들어올 경우)
            V v{2, {0, 1, 2}};
            assert(v.get_capacity() > 2 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        };

        {//복사 생성자
            V o{5, {0, 1, 2}};
            V v{o};
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//이동 생성자
            V o{5, {0, 1, 2}};
            V v{std::move(o)}; 
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//대입
            V o{5, {0, 1, 2}};
            V v{2};
            v = o;
            assert(o.get_capacity() == 5 && o.get_size() == 3 &&              //원본이 변하지 않았는지 확인.
                   o[0] == 0 && o[1] == 1 && o[2] == 2 &&
                   v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }
    
        {//이동
            V o{5, {0, 1, 2}};
            V v{2}; 
            v = std::move(o);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&
                   v[0] == 0 && v[1] == 1 && v[2] == 2 &&
                   o.get_size() == 0);                                         //이동 후 원본이 비어있는지 확인.

            o.push_back({3, 4, 5});                                                //이동 후 원본에 추가해도 정상 작동하는지 확인.
            assert(o.get_size() == 3 && o[0] == 3 && o[1] == 4 && o[2] == 5);
            assert(v.get_capacity() == 5 && v.get_size() == 3 &&                   //이동 후 두 객체가 같은 메모리를 공유하지 않는지 확인.
                   v[0] == 0 && v[1] == 1 && v[2] == 2);
        }

        {//Iterator 생성자

            V v{2, {0, 1, 2}};
            V::Iterator iterator{v.begin()};
            assert(*iterator == 0);
            
            V::Iterator iterator_copy{iterator};
            assert(*iterator_copy == 0);

            V::Iterator iterator_move{std::move(iterator_copy)};
            assert(*iterator_move == 0);

            V::Const_Iterator const_iterator{v.cbegin()};
            assert(*const_iterator == 0);

            V::Const_Iterator const_iterator_copy{const_iterator};
            assert(*const_iterator_copy == 0);

            V::Const_Iterator const_iterator_move{std::move(const_iterator_copy)};
            assert(*const_iterator_move == 0);

        }

        {//iterator
        
            V v{2, {0, 1, 2}};
            auto iterator{v.begin()};
            assert(*iterator == 0);
            ++iterator;
            assert(*iterator == 1);
            ++iterator;
            assert(*iterator == 2);
            --iterator;
            assert(*iterator == 1);
            --iterator;
            assert(*iterator == 0);
            iterator += 2;
            assert(*iterator == 2);
            assert(*(iterator - 2) == 0);
            iterator -= 2;
            assert(*iterator == 0);
            assert(*(iterator + 2) == 2);
            *iterator += 1;
            ++iterator;
            *iterator += 1;
            ++iterator;
            *iterator += 1;
            assert(v[0] == 1 && v[1] == 2 && v[2] == 3);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto const_iterator{v.cbegin()};
            assert(*const_iterator == 0);
            ++const_iterator;
            assert(*const_iterator == 1);
            ++const_iterator;
            assert(*const_iterator == 2);
            --const_iterator;
            assert(*const_iterator == 1);
            --const_iterator;
            assert(*const_iterator == 0);
            const_iterator += 2;
            assert(*const_iterator == 2);
            assert(*(const_iterator - 2) == 0);
            const_iterator -= 2;
            assert(*const_iterator == 0);
            assert(*(const_iterator + 2) == 2);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto reverse_iterator{v.rbegin()};
            assert(*reverse_iterator == 2);
            ++reverse_iterator;
            assert(*reverse_iterator == 1);
            ++reverse_iterator;
            assert(*reverse_iterator == 0);
            --reverse_iterator;
            assert(*reverse_iterator == 1);
            --reverse_iterator;
            assert(*reverse_iterator == 2);
            reverse_iterator += 2;
            assert(*reverse_iterator == 0);
            assert(*(reverse_iterator - 2) == 2);
            reverse_iterator -= 2;
            assert(*reverse_iterator == 2);
            assert(*(reverse_iterator + 2) == 0);
            *reverse_iterator += 1;
            ++reverse_iterator;
            *reverse_iterator += 1;
            ++reverse_iterator;
            *reverse_iterator += 1;
            assert(v[0] == 1 && v[1] == 2 && v[2] == 3);

            v[0] = 0; v[1] = 1; v[2] = 2;
            auto const_reverse_iterator{v.crbegin()};
            assert(*const_reverse_iterator == 2);
            ++const_reverse_iterator;
            assert(*const_reverse_iterator == 1);
            ++const_reverse_iterator;
            assert(*const_reverse_iterator == 0);
            --const_reverse_iterator;
            assert(*const_reverse_iterator == 1);
            --const_reverse_iterator;
            assert(*const_reverse_iterator == 2);
            const_reverse_iterator += 2;
            assert(*const_reverse_iterator == 0);
            assert(*(const_reverse_iterator - 2) == 2);
            const_reverse_iterator -= 2;
            assert(*const_reverse_iterator == 2);
            assert(*(const_reverse_iterator + 2) == 0);

            V temp{2};
            for(auto e : v){ temp.push_back(e); }
            assert(temp[0] == 0 && temp[1] == 1 && temp[2] == 2);

            temp.clear();
            for(const auto e : v){ temp.push_back(e); }
            assert(temp[0] == 0 && temp[1] == 1 && temp[2] == 2);

            temp.clear();
            for(auto e : MIHYIterator_ForEach_Reverse<decltype(v)>(v)){ temp.push_back(e); }
            assert(temp[0] == 2 && temp[1] == 1 && temp[2] == 0);

            temp.clear();
            for(const auto e : MIHYIterator_ForEach_Reverse<decltype(v)>(v)){ temp.push_back(e); }
            assert(temp[0] == 2 && temp[1] == 1 && temp[2] == 0);
            
        }

        {//push_back
            V v{2};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            V v4{2, {7, 8}};
            v.push_back(0);
            v.push_back({1, 2});
            v.push_back(v2);
            v.push_back(std::move(v3));
            v.push_back(v4.begin(), v4.end());
            assert(v[0] == 0 && v[1] == 1 && v[2] == 2 && v[3] == 3 && v[4] == 4 && v[5] == 5 && v[6] == 6 && v[7] == 7 && v[8] == 8);
            assert(v2[0] == 3 && v2[1] == 4);
            //v3는 이동되기 때문에 size가 0입니다. 
            assert(v4[0] == 7 && v4[1] == 8);
            assert(v.get_size() == 9 && v2.get_size() == 2 && v3.get_size() == 0 && v4.get_size() == 2);
        }

        {//push front
            V v{2};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            V v4{2, {7, 8}};
            v.push_front(0);
            v.push_front({1, 2});
            v.push_front(v2);
            v.push_front(std::move(v3));
            v.push_front(v4.begin(), v4.end());
            assert(v[0] == 7 && v[1] == 8 && v[2] == 5 && v[3] == 6 && v[4] == 3 && v[5] == 4 && v[6] == 1 && v[7] == 2 && v[8] == 0);
            assert(v2[0] == 3 && v2[1] == 4);
            //v3는 이동되기 때문에 size가 0입니다. 
            assert(v4[0] == 7 && v4[1] == 8);
            assert(v.get_size() == 9 && v2.get_size() == 2 && v3.get_size() == 0 && v4.get_size() == 2);
        }

        {//push
            V v{2, {0, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 1, 0}};
            V v2{2, {3, 4}};
            V v3{2, {5, 6}};
            V v4{2, {7, 8}};
            v.push(7, 0);
            v.push(7, {1, 2});
            v.push(7, v2);
            v.push(7, std::move(v3));
            v.push(7, v4.begin(), v4.end());
            assert(v[7] == 7 && v[8] == 8 && v[9] == 5 && v[10] == 6 && v[11] == 3 && v[12] == 4 && v[13] == 1 && v[14] == 2 && v[15] == 0);
            assert(v[0] == 0 && v[1] == 1 && v[2] == 1 && v[3] == 1 && v[4] == 2 && v[5] == 2 && v[6] == 2);
            assert(v[16] == 2 && v[17] == 2 && v[18] == 2 && v[19] == 1 && v[20] == 1 && v[21] == 1 && v[22] == 0);
            assert(v2[0] == 3 && v2[1] == 4);
            //v3는 이동되기 때문에 size가 0입니다. 
            assert(v4[0] == 7 && v4[1] == 8);
            assert(v.get_size() == 23 && v2.get_size() == 2 && v3.get_size() == 0 && v4.get_size() == 2);
        }

        {//pop_back
            V v{2, {0, 1, 2}};
            v.pop_back();
            assert(v.get_size() == 2 && v[0] == 0 && v[1] == 1);
            v.pop_back();
            v.pop_back();
            v.pop_back();
            assert(v.get_size() == 0);
        }

        {//pop_front
            V v{2, {0, 1, 2}};
            v.pop_front();
            assert(v.get_size() == 2 && v[0] == 1 && v[1] == 2);
            v.pop_front();
            v.pop_front();
            v.pop_front();
            assert(v.get_size() == 0);
        }

        {//pop
            V v{2, {0, 1, 2, 4, 5}};
            v.pop(2);
            assert(v.get_size() == 4 && v[0] == 0 && v[1] == 1 && v[2] == 4 && v[3] == 5);
            v.pop(0);
            assert(v.get_size() == 3 && v[0] == 1 && v[1] == 4 && v[2] == 5);
            v.pop(2);
            assert(v.get_size() == 2 && v[0] == 1 && v[1] == 4);
            v.pop(0);
            v.pop(0);
            v.pop(0);
            assert(v.get_size() == 0);
        }

    }

    class List_Element{
    public:
        explicit List_Element() : value{-1000}{}
        List_Element(Int64 v) : value{v}{}
        List_Element(const List_Element& lvalue) : value{lvalue.value}{}
        List_Element(List_Element&& rvalue) : value{rvalue.value}{}
        ~List_Element() = default;
        List_Element& operator=(const List_Element& lvalue){
            value = lvalue.value;
            return *this;
        }
        List_Element& operator=(List_Element&& rvalue){
            value = rvalue.value;
            return *this;
        }

        Int64 value;

        bool operator==(const List_Element& v) const{
            return value == v.value;
        }

        bool operator==(Int64 v) const{
            return value == v;
        }

        bool operator!=(Int64 v) const{
            return value != v;
        }

    };

    void mihylist_unittest_assignment_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list);
    void mihylist_unittest_assignment_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list);
    void mihylist_unittest_push_back_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list);
    void mihylist_unittest_push_back_list_lvalue_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list);
    template<typename Container>
    void mihylist_unittest_push_back_iterator_test(std::initializer_list<List_Element> list, Container container);
    void mihylist_unittest_push_front_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list);
    void mihylist_unittest_push_front_list_lvalue_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list);
    template<typename Container>
    void mihylist_unittest_push_front_iterator_test(std::initializer_list<List_Element> list, Container container);
    
    void mihylist_unittest(){

        

        using E = List_Element;
        using L = MIHYList<E>;

        //get_size
        {
            L l{E{10}, E{20}, E{30}};
            assert(l.get_size() == 3);
        }

        //clear
        {
            L l{E{10}, E{20}, E{30}};
            assert(l.get_size() == 3);
            l.clear();
            assert(l.is_empty());
            assert(l.get_size() == 0);
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        //is_empty
        {

            L empty{};
            assert(empty.is_empty());

            L not_empty{E{10}};
            assert(!not_empty.is_empty());

        }

        //get
        {
            L l{E{10}, E{20}, E{30}};
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
        }

        //get_node
        {
            L l{E{10}, E{20}, E{30}};
            assert(l.get_head_node()->value == 10);
            assert(l.get_tail_node()->value == 30);
            assert(l.get_head_node()->next->value == 20);
            assert(l.get_tail_node()->prev->value == 20);
            assert(l.get_head_node()->next->next->value == 30);
            assert(l.get_tail_node()->prev->prev->value == 10);
            assert(l.get_head_node()->next->next->next == l.get_empty_node());
            assert(l.get_tail_node()->prev->prev->prev == l.get_empty_node());

            assert(l.get_head_node()->next->prev == l.get_head_node());
            assert(l.get_tail_node()->prev->next == l.get_tail_node());            

            assert(l.get_head_node()->prev == l.get_empty_node());
            assert(l.get_tail_node()->next == l.get_empty_node());

            assert(l.get_node(0)->value == 10 && l.get_node(1)->value == 20 && l.get_node(2)->value == 30);
        }

        //생성자
        {
            L l{};
            assert(l.is_empty());
            assert(l.get_size() == 0);
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        //생성자(초기화 리스트)
        {
            L l{E{10}, E{20}, E{30}};
            assert(!l.is_empty());
            assert(l.get_size() == 3);
            assert(l.get(0) == 10);
            assert(l.get(1) == 20);
            assert(l.get(2) == 30);
            assert(l.get_head_node()->value == 10);
            assert(l.get_tail_node()->value == 30);
            assert(l.get_head_node()->next->value == 20);
            assert(l.get_tail_node()->prev->value == 20);
            assert(l.get_head_node()->next->prev == l.get_head_node());
            assert(l.get_head_node()->next->next == l.get_tail_node());

            L l2{E{10}};              //원소가 하나인 경우
            assert(!l2.is_empty());
            assert(l2.get_size() == 1);
            assert(l2.get(0) == 10);
            assert(l2.get_head_node() == l2.get_tail_node());
            assert(l2.get_head_node()->prev == l2.get_empty_node());
            assert(l2.get_head_node()->next == l2.get_empty_node());

            L l3{std::initializer_list<E>{}};                   //원소가 없는 경우
            assert(l3.is_empty());
            assert(l3.get_size() == 0);
            assert(l3.get_head_node() == l3.get_empty_node());
            assert(l3.get_tail_node() == l3.get_empty_node());

        }

        //생성자(복사)
        {
            L l{E{10}, E{20}, E{30}};
            L copy{l};
            assert(!l.is_empty());
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
            assert(!copy.is_empty());
            assert(copy.get_size() == 3);
            assert(copy.get(0) == 10 && copy.get(1) == 20 && copy.get(2) == 30);
        }

        //생성자(이동)
        {
            L l{E{10}, E{20}, E{30}};
            L move{std::move(l)};
            assert(l.is_empty());
            assert(l.get_size() == 0);
            assert(!move.is_empty());
            assert(move.get_size() == 3);
            assert(move.get(0) == 10 && move.get(1) == 20 && move.get(2) == 30);
        }

        //생성자(반복자)
        {

            L l{E{10}, E{20}, E{30}};
            L l_to_l{l.begin(), l.end()};
            assert(l_to_l.get_size() == 3);
            

            MIHYVector<E> v{4, {E{10}, E{20}, E{30}}};
            L v_to_l{v.begin(), v.end()};
            assert(v_to_l.get_size() == 3);
            assert(v_to_l.get(0) == 10 && v_to_l.get(1) == 20 && v_to_l.get(2) == 30);

        }

        //대입(초기화 리스트)
        {
            //빈 컨테이너에 대입되는 경우
            #define f mihylist_unittest_assignment_initializer_list_test
            f({}, {});                                                  //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 | 원소의 수가 같을 경우
            f({}, {E{10}});                                             //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({}, {E{10}, E{20}});                                      //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({}, {E{10}, E{20}, E{30}});                               //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head == m_tail인 컨테이너에 대입되는 경우
            f({E{1}}, {});                                              //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 | 원소가 더 적을 경우
            f({E{1}}, {E{10}});                                         //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소의 수가 같을 경우
            f({E{1}}, {E{10}, E{20}});                                  //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({E{1}}, {E{10}, E{20}, E{30}});                           //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head != m_tail인 컨테이너에 대입되는 경우
            f({E{1}, E{2}}, {});                                        //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 |  원소가 더 적을 경우
            f({E{1}, E{2}}, {E{10}});                                   //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  |  원소가 더 적을 경우
            f({E{1}, E{2}}, {E{10}, E{20}});                            //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소의 수가 같을 경우
            f({E{1}, E{2}}, {E{10}, E{20}, E{30}});                     //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head != m_tail인 경우 + m_head와 m_tail사이에 원소가 있을 경우의 컨테이너에 대입되는 경우
            auto init_list = {E{1}, E{2}, E{3}, E{4}, E{5}};
            f(init_list, {});                                           //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 |  원소가 더 적을 경우
            f(init_list, {E{10}});                                      //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  |  원소가 더 적을 경우
            f(init_list, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 적을 경우
            f(init_list, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 적을 경우
            f(init_list, {E{10}, E{20}, E{30}, E{40}, E{50}});          //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소의 수가 같을 경우
            f(init_list, {E{10}, E{20}, E{30}, E{40}, E{50}, E{60}});   //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우
            #undef f
        }

        //대입(복사)
        {
            //빈 컨테이너에 대입되는 경우
            #define f mihylist_unittest_assignment_test
            f({}, {});                                                  //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 | 원소의 수가 같을 경우
            f({}, {E{10}});                                             //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({}, {E{10}, E{20}});                                      //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({}, {E{10}, E{20}, E{30}});                               //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head == m_tail인 컨테이너에 대입되는 경우
            f({E{1}}, {});                                              //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 | 원소가 더 적을 경우
            f({E{1}}, {E{10}});                                         //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소의 수가 같을 경우
            f({E{1}}, {E{10}, E{20}});                                  //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 많을 경우
            f({E{1}}, {E{10}, E{20}, E{30}});                           //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head != m_tail인 컨테이너에 대입되는 경우
            f({E{1}, E{2}}, {});                                        //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 |  원소가 더 적을 경우
            f({E{1}, E{2}}, {E{10}});                                   //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  |  원소가 더 적을 경우
            f({E{1}, E{2}}, {E{10}, E{20}});                            //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소의 수가 같을 경우
            f({E{1}, E{2}}, {E{10}, E{20}, E{30}});                     //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우

            //m_head != m_tail인 경우 + m_head와 m_tail사이에 원소가 있을 경우의 컨테이너에 대입되는 경우
            auto init_list = {E{1}, E{2}, E{3}, E{4}, E{5}};
            f(init_list, {});                                           //복사 대상이 비었을 경우             |  m_head와 m_tail사이에 원소가 없을 경우 |  원소가 더 적을 경우
            f(init_list, {E{10}});                                      //복사 대상의 m_head == m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  |  원소가 더 적을 경우
            f(init_list, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 없을 경우  | 원소가 더 적을 경우
            f(init_list, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 적을 경우
            f(init_list, {E{10}, E{20}, E{30}, E{40}, E{50}});          //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소의 수가 같을 경우
            f(init_list, {E{10}, E{20}, E{30}, E{40}, E{50}, E{60}});   //복사 대상의 m_head != m_tail일 경우 | m_head와 m_tail사이에 원소가 있을 경우  | 원소가 더 많을 경우
            #undef f
        }

        //대입(이동)
        {
            L l{E{10}, E{20}, E{30}};
            L move{};
            move = std::move(l);
            assert(l.get_size() == 0);
            assert(!move.is_empty());
            assert(move.get_size() == 3);
            assert(move.get(0) == 10 && move.get(1) == 20 && move.get(2) == 30);
        }

        //Iterator begin, end
        {

            L l{E{10}, E{20}, E{30}, E{40}};

            //begin
            L::Iterator                 iterator_begin{l.begin()};
            L::Const_Iterator           const_iterator_begin{l.cbegin()};
            L::Reverse_Iterator         reverse_iterator_begin{l.rbegin()};
            L::Const_Reverse_Iterator   const_reverse_iterator_begin{l.crbegin()};

            //end
            L::Iterator                 iterator_end{l.end()};
            L::Const_Iterator           const_iterator_end{l.cend()};
            L::Reverse_Iterator         reverse_iterator_end{l.rend()};
            L::Const_Reverse_Iterator   const_reverse_iterator_end{l.crend()};

            assert(iterator_begin.get_node() == l.get_head_node());
            assert(const_iterator_begin.get_node() == l.get_head_node());
            assert(reverse_iterator_begin.get_node() == l.get_tail_node());
            assert(const_reverse_iterator_begin.get_node() == l.get_tail_node());

            assert(iterator_end.get_node() == l.get_empty_node());
            assert(const_iterator_end.get_node() == l.get_empty_node());
            assert(reverse_iterator_end.get_node() == l.get_empty_node());
            assert(const_reverse_iterator_end.get_node() == l.get_empty_node());

        }

        //Iterator 생성자, 대입, 이동 연산자
        {

            L l{E{10}, E{20}, E{30}, E{40}};

            //기본 생성자
            L::Iterator                 iterator{};
            L::Const_Iterator           const_iterator{};
            L::Reverse_Iterator         reverse_iterator{};
            L::Const_Reverse_Iterator   const_reverse_iterator{};
            assert(iterator.get_node() == nullptr);
            assert(const_iterator.get_node() == nullptr);
            assert(reverse_iterator.get_node() == nullptr);
            assert(const_reverse_iterator.get_node() == nullptr);

            L::Iterator                 iterator_begin{l.begin()};
            L::Const_Iterator           const_iterator_begin{l.cbegin()};
            L::Reverse_Iterator         reverse_iterator_begin{l.rbegin()};
            L::Const_Reverse_Iterator   const_reverse_iterator_begin{l.crbegin()};

            //복사 생성자
            L::Iterator                 iterator_copy{iterator_begin};
            L::Const_Iterator           const_iterator_copy{const_iterator_begin};
            L::Reverse_Iterator         reverse_iterator_copy{reverse_iterator_begin};
            L::Const_Reverse_Iterator   const_reverse_iterator_copy{const_reverse_iterator_begin};

            assert(iterator_copy.get_node() == l.get_head_node());
            assert(const_iterator_copy.get_node() == l.get_head_node());
            assert(reverse_iterator_copy.get_node() == l.get_tail_node());
            assert(const_reverse_iterator_copy.get_node() == l.get_tail_node());

            //이동 생성자
            L::Iterator                 iterator_move{std::move(iterator_begin)};
            L::Const_Iterator           const_iterator_move{std::move(const_iterator_begin)};
            L::Reverse_Iterator         reverse_iterator_move{std::move(reverse_iterator_begin)};
            L::Const_Reverse_Iterator   const_reverse_iterator_move{std::move(const_reverse_iterator_begin)};

            assert(iterator_move.get_node() == l.get_head_node());
            assert(const_iterator_move.get_node() == l.get_head_node());
            assert(reverse_iterator_move.get_node() == l.get_tail_node());
            assert(const_reverse_iterator_move.get_node() == l.get_tail_node());

            //반복자 종류별 상호 변환
            L::Iterator                const_to_iterator{l.cbegin()};
            L::Iterator                reverse_to_iterator{l.rbegin()};
            L::Iterator                reverse_const_to_iterator{l.crbegin()};
            assert(*const_to_iterator == *l.cbegin());
            assert(*reverse_to_iterator == *l.rbegin());
            assert(*reverse_const_to_iterator == *l.crbegin());

            L::Const_Iterator           iterator_to_const{l.begin()};
            L::Const_Iterator           reverse_to_const{l.rbegin()};
            L::Const_Iterator           reverse_const_to_const{l.crbegin()};
            assert(*iterator_to_const == *l.begin());
            assert(*reverse_to_const == *l.rbegin());
            assert(*reverse_const_to_const == *l.crbegin());

            L::Reverse_Iterator         iterator_to_reverse{l.begin()};
            L::Reverse_Iterator         const_to_reverse{l.cbegin()};
            L::Reverse_Iterator         reverse_const_to_reverse{l.crbegin()};
            assert(*iterator_to_reverse == *l.begin());
            assert(*const_to_reverse == *l.cbegin());
            assert(*reverse_const_to_reverse == *l.crbegin());

            L::Const_Reverse_Iterator   iterator_to_reverse_const{l.begin()};
            L::Const_Reverse_Iterator   const_to_reverse_const{l.cbegin()};
            L::Const_Reverse_Iterator   reverse_to_reverse_const{l.rbegin()};
            assert(*iterator_to_reverse_const == *l.begin());
            assert(*const_to_reverse_const == *l.cbegin());
            assert(*reverse_to_reverse_const == *l.rbegin());

            //대입 연산자
            iterator_begin                  = iterator_copy;
            const_iterator_begin            = const_iterator_copy;
            reverse_iterator_begin          = reverse_iterator_copy;
            const_reverse_iterator_begin    = const_reverse_iterator_copy;

            assert(iterator_begin.get_node() == l.get_head_node());
            assert(const_iterator_begin.get_node() == l.get_head_node());
            assert(reverse_iterator_begin.get_node() == l.get_tail_node());
            assert(const_reverse_iterator_begin.get_node() == l.get_tail_node());

            //이동 연산자
            L::Iterator                 iterator_move_assign{std::move(iterator_begin)};
            L::Const_Iterator           const_iterator_move_assign{std::move(const_iterator_begin)};
            L::Reverse_Iterator         reverse_iterator_move_assign{std::move(reverse_iterator_begin)};
            L::Const_Reverse_Iterator   const_reverse_iterator_move_assign{std::move(const_reverse_iterator_begin)};

            assert(iterator_move_assign.get_node() == l.get_head_node());
            assert(const_iterator_move_assign.get_node() == l.get_head_node());
            assert(reverse_iterator_move_assign.get_node() == l.get_tail_node());
            assert(const_reverse_iterator_move_assign.get_node() == l.get_tail_node());

        }

        //Iterator *, ->, ==, !=, ++, --
        {

            L l{E{10}, E{20}, E{30}, E{40}};

            L::Iterator                 iterator{l.begin()};
            L::Const_Iterator           const_iterator{l.cbegin()};
            L::Reverse_Iterator         reverse_iterator{l.rbegin()};
            L::Const_Reverse_Iterator   const_reverse_iterator{l.crbegin()};

            //operator*
            assert(*iterator == 10);
            assert(*const_iterator == 10);
            assert(*reverse_iterator == 40);
            assert(*const_reverse_iterator == 40);

            //operator->
            assert(iterator->value == 10);
            assert(const_iterator->value == 10);
            assert(reverse_iterator->value == 40);
            assert(const_reverse_iterator->value == 40);

            //operator==, operator!=
            assert(iterator == l.begin());
            assert(iterator != l.end());
            assert(const_iterator == l.cbegin());
            assert(const_iterator != l.cend());
            assert(reverse_iterator == l.rbegin());
            assert(reverse_iterator != l.rend());
            assert(const_reverse_iterator == l.crbegin());
            assert(const_reverse_iterator != l.crend());

            //operator++, operator++(int)
            ++iterator;
            ++const_iterator;
            ++reverse_iterator;
            ++const_reverse_iterator;

            assert(*(iterator++) == 20);
            assert(*(const_iterator++) == 20);
            assert(*(reverse_iterator++) == 30);
            assert(*(const_reverse_iterator++) == 30);

            assert(*iterator == 30);
            assert(*const_iterator == 30);
            assert(*reverse_iterator == 20);
            assert(*const_reverse_iterator == 20);

            assert(*(++iterator) == 40);
            assert(*(++const_iterator) == 40);
            assert(*(++reverse_iterator) == 10);
            assert(*(++const_reverse_iterator) == 10);

            //operator--, operator--(int)
            --iterator;
            --const_iterator;
            --reverse_iterator;
            --const_reverse_iterator;

            assert(*(iterator--) == 30);
            assert(*(const_iterator--) == 30);
            assert(*(reverse_iterator--) == 20);
            assert(*(const_reverse_iterator--) == 20);

            assert(*iterator == 20);
            assert(*const_iterator == 20);
            assert(*reverse_iterator == 30);
            assert(*const_reverse_iterator == 30);

            assert(*(--iterator) == 10);
            assert(*(--const_iterator) == 10);
            assert(*(--reverse_iterator) == 40);
            assert(*(--const_reverse_iterator) == 40);

        }

        //Iterator foreach
        {

            L           l{E{10}, E{20}, E{30}, E{40}};
            const L&    cl{l};
            L           temp{};

            for(auto& e : l){ temp.push_back(e); }
            assert(temp.get_size() == 4);
            assert(temp.get(0) == 10 && temp.get(1) == 20 && temp.get(2) == 30 && temp.get(3) == 40);

            temp.clear();
            for(const auto& e : cl){ temp.push_back(e); }
            assert(temp.get_size() == 4);
            assert(temp.get(0) == 10 && temp.get(1) == 20 && temp.get(2) == 30 && temp.get(3) == 40);

            temp.clear();
            for(auto& e : MIHYIterator_ForEach_Reverse<L>(l)){ temp.push_back(e); }
            assert(temp.get_size() == 4);
            assert(temp.get(0) == 40 && temp.get(1) == 30 && temp.get(2) == 20 && temp.get(3) == 10);

            temp.clear();
            for(const auto& e : MIHYIterator_ForEach_Reverse<const L>(cl)){ temp.push_back(e); }
            assert(temp.get_size() == 4);
            assert(temp.get(0) == 40 && temp.get(1) == 30 && temp.get(2) == 20 && temp.get(3) == 10);

        }

        //push_back(lvalue)
        {

            E e0{10};
            E e1{20};
            E e2{30};

            L l{};
            l.push_back(e0);         //리스트가 비었을 경우
            l.push_back(e1);         //m_head == m_tail일 경우
            l.push_back(e2);         //m_head != m_tail일 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

        }

        //push_back(rvalue)
        {

            L l{};
            l.push_back(E{10});         //리스트가 비었을 경우
            l.push_back(E{20});         //m_head == m_tail일 경우
            l.push_back(E{30});         //m_head != m_tail일 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

        }
        
        //push_back(초기화 리스트)
        {

            //빈 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({}, {});                                           //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({}, {E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_initializer_list_test({}, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_initializer_list_test({}, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}}, {});                                       //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}}, {E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}}, {E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}}, {E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}}, {});                                 //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}}, {E{10}});                            //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}}, {E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}}, {E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}, E{3}}, {});                           //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}, E{3}}, {E{10}});                      //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}, E{3}}, {E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_initializer_list_test({E{1}, E{2}, E{3}}, {E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

        }

        //push_back(List lvalue)
        {

            //빈 리스트인 경우
            #define f mihylist_unittest_push_back_list_lvalue_test
            f({}, {});                                           //복사 대상이 빈 리스트인 경우
            f({}, {E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            f({}, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({}, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            f({E{1}}, {});                                       //복사 대상이 빈 리스트인 경우
            f({E{1}}, {E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            f({E{1}}, {E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}}, {E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            f({E{1}, E{2}}, {});                                 //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}}, {E{10}});                            //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}}, {E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}}, {E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            f({E{1}, E{2}, E{3}}, {});                           //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}, E{3}}, {E{10}});                      //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우
            #undef f

        }
        
        //push_back(List rvalue)
        {

            L l{};                          //빈 컨테이너로 이동
            L move{E{10}, E{20}, E{30}};
            l.push_back(std::move(move));
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
            assert(move.get_size() == 0);
            assert(move.get_head_node() == move.get_empty_node());
            assert(move.get_tail_node() == move.get_empty_node());

            L move2{E{40}};                 //비지 않은 컨테이너로 이동
            l.push_back(std::move(move2));
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40);
            assert(move2.get_size() == 0);
            assert(move2.get_head_node() == move2.get_empty_node());
            assert(move2.get_tail_node() == move2.get_empty_node());

        }

        //push_back(Iterator)
        {

            //빈 리스트인 경우
            #define f mihylist_unittest_push_back_iterator_test
            f({}, std::initializer_list<E>{});                                           //복사 대상이 빈 리스트인 경우
            f({}, std::initializer_list<E>{E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            f({}, std::initializer_list<E>{E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({}, std::initializer_list<E>{E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            f({E{1}}, std::initializer_list<E>{});                                       //복사 대상이 빈 리스트인 경우
            f({E{1}}, std::initializer_list<E>{E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            f({E{1}}, std::initializer_list<E>{E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}}, std::initializer_list<E>{E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{});                                 //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}});                            //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{});                           //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}});                      //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우
            #undef f

        }
        
        //push_front(lvalue)
        {

            E e0{10};
            E e1{20};
            E e2{30};

            L l{};
            l.push_front(e0);         //리스트가 비었을 경우
            l.push_front(e1);         //m_head == m_tail일 경우
            l.push_front(e2);         //m_head != m_tail일 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 30 && l.get(1) == 20 && l.get(2) == 10);

        }

        //push_front(rvalue)
        {

            L l{};
            l.push_front(E{10});         //리스트가 비었을 경우
            l.push_front(E{20});         //m_head == m_tail일 경우
            l.push_front(E{30});         //m_head != m_tail일 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 30 && l.get(1) == 20 && l.get(2) == 10);

        }

        //push_front(초기화 리스트)
        {
            
            //빈 리스트인 경우
            #define f mihylist_unittest_push_front_initializer_list_test
            f({}, {});                                           //복사 대상이 빈 리스트인 경우
            f({}, {E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            f({}, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({}, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            f({E{1}}, {});                                       //복사 대상이 빈 리스트인 경우
            f({E{1}}, {E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            f({E{1}}, {E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}}, {E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            f({E{1}, E{2}}, {});                                 //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}}, {E{10}});                            //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}}, {E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}}, {E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            f({E{1}, E{2}, E{3}}, {});                           //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}, E{3}}, {E{10}});                      //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우
            #undef f

        }

        //push_front(List lvalue)
        {
            
            //빈 리스트인 경우
            #define f mihylist_unittest_push_front_list_lvalue_test
            f({}, {});                                           //복사 대상이 빈 리스트인 경우
            f({}, {E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            f({}, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({}, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            f({E{1}}, {});                                       //복사 대상이 빈 리스트인 경우
            f({E{1}}, {E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            f({E{1}}, {E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}}, {E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            f({E{1}, E{2}}, {});                                 //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}}, {E{10}});                            //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}}, {E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}}, {E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            f({E{1}, E{2}, E{3}}, {});                           //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}, E{3}}, {E{10}});                      //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}, E{3}}, {E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우
            #undef f

        }

        //push_front(List rvalue)
        {

            L l{};                          //빈 컨테이너로 이동
            L move{E{10}, E{20}, E{30}};
            l.push_front(std::move(move));
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
            assert(move.get_size() == 0);
            assert(move.get_head_node() == move.get_empty_node());
            assert(move.get_tail_node() == move.get_empty_node());

            L move2{E{40}};                 //비지 않은 컨테이너로 이동
            l.push_front(std::move(move2));
            assert(l.get(0) == 40 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 30);
            assert(move2.get_size() == 0);
            assert(move2.get_head_node() == move2.get_empty_node());
            assert(move2.get_tail_node() == move2.get_empty_node());
            
        }
        
        //push_front(Iterator)
        {
            
            //빈 리스트인 경우
            #define f mihylist_unittest_push_front_iterator_test
            f({}, std::initializer_list<E>{});                                           //복사 대상이 빈 리스트인 경우
            f({}, std::initializer_list<E>{E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            f({}, std::initializer_list<E>{E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({}, std::initializer_list<E>{E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            f({E{1}}, std::initializer_list<E>{});                                       //복사 대상이 빈 리스트인 경우
            f({E{1}}, std::initializer_list<E>{E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            f({E{1}}, std::initializer_list<E>{E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}}, std::initializer_list<E>{E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{});                                 //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}});                            //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}}, std::initializer_list<E>{E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{});                           //복사 대상이 빈 리스트인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}});                      //복사 대상의 m_head == m_tail인 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            f({E{1}, E{2}, E{3}}, std::initializer_list<E>{E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우
            #undef f

        }

        //push_left(Index, lvalue)
        //push_left(Index, rvalue)
        //push_left(Index, 초기화 리스트)
        //push_left(Index, List lvalue)
        //push_left(Index, List rvalue)
        //push_left(Index, Iterator)
        //push_left(Iterator, lvalue)
        //push_left(Iterator, rvalue)
        //push_left(Iterator, 초기화 리스트)
        //push_left(Iterator, List lvalue)
        //push_left(Iterator, List rvalue)
        //push_left(Iterator, Iterator)
        //위 함수들은 내부에서 push_node_left(Node, ...)를 호출합니다. 따라서 push_node_left(Node, ...)의 테스트를 통해 검사합니다.
        {

            //함수 시그니처 검사
            L l{};
            E e{};
            L l2{E{}, E{}, E{}};
            l.push_left(0, e);
            l.push_left(0, E{});
            l.push_left(0, {e, e, e});
            l.push_left(0, l2);
            l.push_left(0, L{e, e, e});
            l.push_left(0, l2.begin(), l2.end());

            l.clear();
            l.push_left(l.begin(), e);
            l.push_left(l.begin(), E{});
            l.push_left(l.begin(), {e, e, e});
            l.push_left(l.begin(), l2);
            l.push_left(l.begin(), L{e, e, e});
            l.push_left(l.begin(), l2.begin(), l2.end());

        }

        //push_node_left(Node, lvalue)
        {
                
            E e0{10};
            E e1{20};
            E e2{30};
            E e3{40};
            E e4{50};

            L l{};
            l.push_node_left(&l.m_empty_node,              e0);           //리스트가 비었을 경우              10
            l.push_node_left(l.m_empty_node.next,          e1);           //head                           20 10
            l.push_node_left(l.m_empty_node.prev,          e2);           //tail                          20 30 10
            l.push_node_left(l.m_empty_node.next->next,    e3);           //중간 노드                    20 40 30 10
            l.push_node_left(&l.m_empty_node,              e4);           //empty_node                 20 40 30 10 50
            assert(l.get_size() == 5);
            assert(l.get(0) == 20 && l.get(1) == 40 && l.get(2) == 30 && l.get(3) == 10 && l.get(4) == 50);
            
        }

        //push_node_left(Node, rvalue)
        {

            L l{};
            l.push_node_left(&l.m_empty_node,           E{10});           //리스트가 비었을 경우              10
            l.push_node_left(l.m_empty_node.next,       E{20});           //head                           20 10
            l.push_node_left(l.m_empty_node.prev,       E{30});           //tail                          20 30 10
            l.push_node_left(l.m_empty_node.next->next, E{40});           //중간 노드                    20 40 30 10
            l.push_node_left(&l.m_empty_node,           E{50});           //empty_node                 20 40 30 10 50
            assert(l.get_size() == 5);
            assert(l.get(0) == 20 && l.get(1) == 40 && l.get(2) == 30 && l.get(3) == 10 && l.get(4) == 50);

        }

        //push_node_left(Node, 초기화 리스트)        내부에서 push_node_left(Node, Iterator)를 호출합니다. 따라서 push_node_left(Node, Iterator)의 테스트를 통해 검사합니다.
        //push_node_left(Node, List lvalue)         내부에서 push_node_left(Node, Iterator)를 호출합니다. 따라서 push_node_left(Node, Iterator)의 테스트를 통해 검사합니다.
        {

            //함수 시그니처 검사
            L l;
            L l2;
            l.push_node_left(&l.m_empty_node, {E{}, E{}, E{}});
            l.push_node_left(&l.m_empty_node, l2);

        }
        
        //push_node_left(Node, List rvalue)
        {

            L l{};
            l.push_node_left(&l.m_empty_node, L{E{10}, E{20}, E{30}});                         //리스트가 비었을 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

            l = {E{40}};
            l.push_node_left(l.m_empty_node.next, L{E{10}, E{20}, E{30}});                     //원소가 하나일 경우(head == tail)
            assert(l.get_size() == 4);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40);

            l = {E{40}, E{50}, E{60}};
            l.push_node_left(l.m_empty_node.next, L{E{10}, E{20}, E{30}});                     //head
            assert(l.get_size() == 6);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40 && l.get(4) == 50 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}};
            l.push_node_left(l.m_empty_node.prev, L{E{10}, E{20}, E{30}});                     //tail
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}, E{70}};
            l.push_node_left(l.m_empty_node.next->next->next, L{E{10}, E{20}, E{30}});         //중간 노드
            assert(l.get_size() == 7);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30 && l.get(5) == 60 && l.get(6) == 70);

            l = {E{40}, E{50}};
            l.push_node_left(&l.m_empty_node, L{E{10}, E{20}, E{30}});                        //empty_node
            assert(l.get_size() == 5);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30);
            
        }

        //push_node_left(Node, Iterator)
        {

            L container{E{10}, E{20}, E{30}};

            L l{};
            l.push_node_left(&l.m_empty_node, container.begin(), container.end());                         //리스트가 비었을 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

            l = {E{40}};
            l.push_node_left(l.m_empty_node.next, container.begin(), container.end());                     //원소가 하나일 경우(head == tail)
            assert(l.get_size() == 4);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40);

            l = {E{40}, E{50}, E{60}};
            l.push_node_left(l.m_empty_node.next, container.begin(), container.end());                     //head
            assert(l.get_size() == 6);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40 && l.get(4) == 50 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}};
            l.push_node_left(l.m_empty_node.prev, container.begin(), container.end());                     //tail
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}, E{70}};
            l.push_node_left(l.m_empty_node.next->next->next, container.begin(), container.end());         //중간 노드
            assert(l.get_size() == 7);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30 && l.get(5) == 60 && l.get(6) == 70);

            l = {E{40}, E{50}};
            l.push_node_left(&l.m_empty_node, container.begin(), container.end());                        //empty_node
            assert(l.get_size() == 5);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 10 && l.get(3) == 20 && l.get(4) == 30);

        }


        //push_right(Index, lvalue)
        //push_right(Index, rvalue)
        //push_right(Index, 초기화 리스트)
        //push_right(Index, List lvalue)
        //push_right(Index, List rvalue)
        //push_right(Index, Iterator)
        //push_right(Iterator, lvalue)
        //push_right(Iterator, rvalue)
        //push_right(Iterator, 초기화 리스트)
        //push_right(Iterator, List lvalue)
        //push_right(Iterator, List rvalue)
        //push_right(Iterator, Iterator)
        //위 함수들은 내부에서 push_node_right(Node, ...)를 호출합니다. 따라서 push_node_right(Node, ...)의 테스트를 통해 검사합니다.
        {

            //함수 시그니처 검사
            L l{};
            E e{};
            L l2{E{}, E{}, E{}};
            l.push_right(0, e);
            l.push_right(0, E{});
            l.push_right(0, {e, e, e});
            l.push_right(0, l2);
            l.push_right(0, L{e, e, e});
            l.push_right(0, l2.begin(), l2.end());

        }

        //push_right(Node, lvalue)
        {
                
            E e0{10};
            E e1{20};
            E e2{30};
            E e3{40};
            E e4{50};

            L l{};
            l.push_node_right(&l.m_empty_node,              e0);           //리스트가 비었을 경우              10
            l.push_node_right(l.m_empty_node.next,          e1);           //head                           10 20
            l.push_node_right(l.m_empty_node.prev,          e2);           //tail                          10 20 30
            l.push_node_right(l.m_empty_node.next->next,    e3);           //중간 노드                    10 20 40 30
            l.push_node_right(&l.m_empty_node,              e4);           //empty_node                 50 10 20 40 30
            assert(l.get_size() == 5);
            assert(l.get(0) == 50 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 40 && l.get(4) == 30);
            
        }

        //push_node_right(Node, rvalue)
        {

            L l{};
            l.push_node_right(&l.m_empty_node,           E{10});           //리스트가 비었을 경우              10
            l.push_node_right(l.m_empty_node.next,       E{20});           //head                           10 20
            l.push_node_right(l.m_empty_node.prev,       E{30});           //tail                          10 20 30
            l.push_node_right(l.m_empty_node.next->next, E{40});           //중간 노드                    10 20 40 30
            l.push_node_right(&l.m_empty_node,           E{50});           //empty_node                 50 10 20 40 30
            assert(l.get_size() == 5);
            assert(l.get(0) == 50 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 40 && l.get(4) == 30);

        }

        //push_node_right(Node, 초기화 리스트)        내부에서 push_node_right(Node, Iterator)를 호출합니다. 따라서 push_node_right(Node, Iterator)의 테스트를 통해 검사합니다.
        //push_node_right(Node, List lvalue)         내부에서 push_node_right(Node, Iterator)를 호출합니다. 따라서 push_node_right(Node, Iterator)의 테스트를 통해 검사합니다.
        
        //push_node_right(Node, List rvalue)
        {
                
            L l{};
            l.push_node_right(&l.m_empty_node, L{E{10}, E{20}, E{30}});                         //리스트가 비었을 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

            l = {E{40}};
            l.push_node_right(l.m_empty_node.next, L{E{10}, E{20}, E{30}});                     //원소가 하나일 경우(head == tail)
            assert(l.get_size() == 4);
            assert(l.get(0) == 40 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 30);

            l = {E{40}, E{50}, E{60}};
            l.push_node_right(l.m_empty_node.next, L{E{10}, E{20}, E{30}});                     //head
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 30 && l.get(4) == 50 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}};
            l.push_node_right(l.m_empty_node.prev, L{E{10}, E{20}, E{30}});                     //tail
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 60 && l.get(3) == 10 && l.get(4) == 20 && l.get(5) == 30);

            l = {E{40}, E{50}, E{60}, E{70}};
            l.push_node_right(l.m_empty_node.next->next->next, L{E{10}, E{20}, E{30}});         //중간 노드
            assert(l.get_size() == 7);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 60 && l.get(3) == 10 && l.get(4) == 20 && l.get(5) == 30 && l.get(6) == 70);

            l = {E{40}, E{50}};
            l.push_node_right(&l.m_empty_node, L{E{10}, E{20}, E{30}});                        //empty_node
            assert(l.get_size() == 5);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40 && l.get(4) == 50);

        }

        //push_node_right(Node, Iterator)
        {

            L container{E{10}, E{20}, E{30}};

            L l{};
            l.push_node_right(&l.m_empty_node, container.begin(), container.end());                         //리스트가 비었을 경우
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

            l = {E{40}};
            l.push_node_right(l.m_empty_node.next, container.begin(), container.end());                     //원소가 하나일 경우(head == tail)
            assert(l.get_size() == 4);
            assert(l.get(0) == 40 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 30);

            l = {E{40}, E{50}, E{60}};
            l.push_node_right(l.m_empty_node.next, container.begin(), container.end());                     //head
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 10 && l.get(2) == 20 && l.get(3) == 30 && l.get(4) == 50 && l.get(5) == 60);

            l = {E{40}, E{50}, E{60}};
            l.push_node_right(l.m_empty_node.prev, container.begin(), container.end());                     //tail
            assert(l.get_size() == 6);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 60 && l.get(3) == 10 && l.get(4) == 20 && l.get(5) == 30);

            l = {E{40}, E{50}, E{60}, E{70}};
            l.push_node_right(l.m_empty_node.next->next->next, container.begin(), container.end());         //중간 노드
            assert(l.get_size() == 7);
            assert(l.get(0) == 40 && l.get(1) == 50 && l.get(2) == 60 && l.get(3) == 10 && l.get(4) == 20 && l.get(5) == 30 && l.get(6) == 70);

            l = {E{40}, E{50}};
            l.push_node_right(&l.m_empty_node, container.begin(), container.end());                        //empty_node
            assert(l.get_size() == 5);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40 && l.get(4) == 50);

        }

        //pop_back
        {

            L l{E{10}, E{20}, E{30}, E{40}, E{50}};
            l.pop_back();
            assert(l.get_size() == 4);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30 && l.get(3) == 40);
            l.pop_back();
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);

        }

        //pop_front
        {

            L l{E{10}, E{20}, E{30}, E{40}, E{50}};
            l.pop_front();
            assert(l.get_size() == 4);
            assert(l.get(0) == 20 && l.get(1) == 30 && l.get(2) == 40 && l.get(3) == 50);
            l.pop_front();
            assert(l.get_size() == 3);
            assert(l.get(0) == 30 && l.get(1) == 40 && l.get(2) == 50);
        }

        //pop(Index)
        {

            L l{E{10}, E{20}, E{30}, E{40}, E{50}};
            l.pop(2);
            assert(l.get_size() == 4);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 40 && l.get(3) == 50);
            l.pop(0);
            assert(l.get_size() == 3);
            assert(l.get(0) == 20 && l.get(1) == 40 && l.get(2) == 50);
            l.pop(l.get_size() - 1);
            assert(l.get_size() == 2);
            assert(l.get(0) == 20 && l.get(1) == 40);

        }

        {

            L l{E{10}, E{20}, E{30}, E{40}, E{50}};
            l.pop(++++l.begin());
            assert(l.get_size() == 4);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 40 && l.get(3) == 50);
            l.pop(l.begin());
            assert(l.get_size() == 3);
            assert(l.get(0) == 20 && l.get(1) == 40 && l.get(2) == 50);
            l.pop(--l.end());
            assert(l.get_size() == 2);
            assert(l.get(0) == 20 && l.get(1) == 40);

        }


    }

    void mihylist_unittest_assignment_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list){

        MIHYList<List_Element> l{list};
        MIHYList<List_Element> copy{copy_list};

        l = copy;

        assert(l.get_size() == copy_list.size());           //사이즈를 검사합니다.

        auto    iter{copy_list.begin()};                    //원소가 제대로 들어갔는지 검사합니다.
        UInt64  i{0};
        while(iter != copy_list.end()){

            assert(l.get(i) == *iter);
            
            ++iter;
            ++i;
            
        }

    }

    void mihylist_unittest_assignment_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list){

        MIHYList<List_Element> l{list};

        l = copy_list;

        assert(l.get_size() == copy_list.size());           //사이즈를 검사합니다.

        auto    iter{copy_list.begin()};                    //원소가 제대로 들어갔는지 검사합니다.
        UInt64  i{0};
        while(iter != copy_list.end()){

            assert(l.get(i) == *iter);
            
            ++iter;
            ++i;
            
        }

    }

    void mihylist_unittest_push_back_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list){

        MIHYList<List_Element> l{list};

        l.push_back(push_back_list);

        assert(l.get_size() == list.size() + push_back_list.size());

        UInt64 index{0};
        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : push_back_list){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }

    }

    void mihylist_unittest_push_back_list_lvalue_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list){

        MIHYList<List_Element> l{list};
        MIHYList<List_Element> push_back{push_back_list};

        l.push_back(push_back);

        assert(l.get_size() == list.size() + push_back_list.size());

        UInt64 index{0};
        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : push_back_list){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }
        
    }

    template<typename Container>
    void mihylist_unittest_push_back_iterator_test(std::initializer_list<List_Element> list, Container container){

        MIHYList<List_Element> l{list};

        l.push_back(container.begin(), container.end());

        assert(l.get_size() == list.size() + mihyiterator_distance(container.begin(), container.end()));

        UInt64 index{0};
        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : container){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }
        
    }

    void mihylist_unittest_push_front_initializer_list_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list){

        MIHYList<List_Element> l{list};

        l.push_front(push_back_list);

        assert(l.get_size() == list.size() + push_back_list.size());

        UInt64 index{0};
        for(auto& e : push_back_list){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }

    }

    void mihylist_unittest_push_front_list_lvalue_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list){

        MIHYList<List_Element> l{list};
        MIHYList<List_Element> push_back{push_back_list};

        l.push_front(push_back);

        assert(l.get_size() == list.size() + push_back_list.size());

        UInt64 index{0};
        for(auto& e : push_back_list){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }

    }

    template<typename Container>
    void mihylist_unittest_push_front_iterator_test(std::initializer_list<List_Element> list, Container container){

        MIHYList<List_Element> l{list};

        l.push_front(container.begin(), container.end());

        assert(l.get_size() == list.size() + mihyiterator_distance(container.begin(), container.end()));

        UInt64 index{0};
        for(auto& e : container){
            assert(l.get(index) == e);
            ++index;
        }

        for(auto& e : list){
            assert(l.get(index) == e);
            ++index;
        }

        if(l.get_size() == 0){
            assert(l.get_head_node() == l.get_empty_node());
            assert(l.get_tail_node() == l.get_empty_node());
        }

        if(l.get_size() == 1){
            assert(l.get_head_node() == l.get_tail_node());
        }
        
    }

    class HashMapElement{
    public:

        UInt64 m_key;
        UInt64 m_value;

        bool operator==(const HashMapElement& lvalue) const{
            return m_key == lvalue.m_key && m_value == lvalue.m_value;
        }

    };

    void mihyhashmap_unittest(){

        using E = HashMapElement;
        using H = MIHYHashTable<E>;

        auto hash{[](const E& e){return e.m_key;}};

        #define CHECK_ELEMENT(h, key, value)    \
        {                                       \
            E e;                                \
            if(h.find({key, value}, &e)){       \
                assert(e.m_key == key);         \
                assert(e.m_value == value);     \
            }else{                              \
                assert(false);                  \
            }                                   \
        }

        //set_hash_function
        //get_hash_function
        {

            H h{hash};
            E e{10, 20};
            auto hash2{[](const E& e){return e.m_key * 5;}};

            assert(h.get_hash_function()(e) == hash(e));

            h.set_hash_function(hash2);
            assert(h.get_hash_function()(e) == hash2(e));

            //set_hash_function호출 후 재해싱 되는지 확인합니다.
            H h2{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            h2.reserve_bucket_table(20);
            CHECK_ELEMENT(h2, 1, 10);
            CHECK_ELEMENT(h2, 2, 20);
            CHECK_ELEMENT(h2, 3, 30);

            h2.set_hash_function(hash2);
            assert(h2.m_bucket_table.table[1].begin == h2.m_node_list.empty_node);
            assert(h2.m_bucket_table.table[2].begin == h2.m_node_list.empty_node);
            assert(h2.m_bucket_table.table[3].begin == h2.m_node_list.empty_node);
            assert(h2.m_bucket_table.table[5].begin->value.m_key == 1  && h2.m_bucket_table.table[5].begin->value.m_value == 10);
            assert(h2.m_bucket_table.table[10].begin->value.m_key == 2 && h2.m_bucket_table.table[10].begin->value.m_value == 20);
            assert(h2.m_bucket_table.table[15].begin->value.m_key == 3 && h2.m_bucket_table.table[15].begin->value.m_value == 30);

        }

        //get_bucket_table_size
        {

            H h{hash};
            assert(h.get_bucket_table_size() == h.m_bucket_table.size);

        }

        //get_size
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            assert(h.get_size() == 3 && h.get_size() == h.m_node_list.size);

        }

        //get_rehash_threshold
        //set_rehash_threshold
        {

            H h{hash};

            assert(h.get_rehash_threshold() == h.DEFAULT_REHASH_THRESHOLD);
            assert(h.get_rehash_threshold() == h.m_rehash_threshold);


            //set_rehash_threshold을 호출하면 재해싱이 일어나도록 유도합니다.
            h.set_rehash_threshold(0.8f);
            h.reserve_bucket_table(10);
            UInt64 key = 0;
            for(UInt64 i = 0; i < h.get_bucket_table_size() / 2; ++i){
                h.insert(E{key, key * 10});
                ++key;
            }

            //재해싱 확인
            UInt64 bucket_table_size_before{h.get_bucket_table_size()};
            h.set_rehash_threshold(0.3f);
            assert(h.get_bucket_table_size() > bucket_table_size_before);
            
            for(UInt64 i = 0; i < key; ++i){
                CHECK_ELEMENT(h, i, i * 10);
            }

        }

        //clear
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            assert(h.get_size() == 3);

            h.clear();
            assert(h.get_size() == 0);
            for(UInt64 i = 0; i < h.get_bucket_table_size(); ++i){
                assert(h.m_bucket_table.table[i].begin == h.m_node_list.empty_node);
            }

        }

        //reserve_bucket_table
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            UInt64 bucket_table_size_before{h.get_bucket_table_size()};
            h.reserve_bucket_table(bucket_table_size_before * 2);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            assert(h.get_bucket_table_size() >= bucket_table_size_before * 2);

        }

        //Iterator begin, end
        //Iterator operator=(복사)
        //Iterator operator=(이동)
        //Iterator operator*
        //Iterator operator->
        //Iterator operator++
        //Iterator operator--
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            auto begin{h.begin()};
            auto cbegin{h.cbegin()};
            auto rbegin{h.rbegin()};
            auto crbegin{h.crbegin()};
            auto end{h.end()};
            auto cend{h.cend()};
            auto rend{h.rend()};
            auto crend{h.crend()};
            auto assign_begin{begin};
            auto assign_cbegin{cbegin};
            auto assign_rbegin{rbegin};
            auto assign_crbegin{crbegin};
            auto assign_end{end};
            auto assign_cend{cend};
            auto assign_rend{rend};
            auto assign_crend{crend};

            assert(*begin == E(1, 10));
            assert(*cbegin == E(1, 10));
            assert(*rbegin == E(3, 30));
            assert(*crbegin == E(3, 30));
            assert(begin->m_key == 1 && begin->m_value == 10);
            assert(cbegin->m_key == 1 && cbegin->m_value == 10);
            assert(rbegin->m_key == 3 && rbegin->m_value == 30);
            assert(crbegin->m_key == 3 && crbegin->m_value == 30);


            for(auto iter{begin}; iter != end; ++iter){}            //end들이 반복자의 마지막 역할을 하는지 확인합니다.
            for(auto iter{cbegin}; iter != cend; ++iter){}
            for(auto iter{rbegin}; iter != rend; ++iter){}
            for(auto iter{crbegin}; iter != crend; ++iter){}

            assign_begin    = begin;
            assign_cbegin   = cbegin;
            assign_rbegin   = rbegin;
            assign_crbegin  = crbegin;
            assign_end      = end;
            assign_cend     = cend;
            assign_rend     = rend;
            assign_crend    = crend;
            assert(*assign_begin == E(1, 10));
            assert(*assign_cbegin == E(1, 10));
            assert(*assign_rbegin == E(3, 30));
            assert(*assign_crbegin == E(3, 30));
            assert(assign_begin->m_key == 1 && assign_begin->m_value == 10);
            assert(assign_cbegin->m_key == 1 && assign_cbegin->m_value == 10);
            assert(assign_rbegin->m_key == 3 && assign_rbegin->m_value == 30);
            assert(assign_crbegin->m_key == 3 && assign_crbegin->m_value == 30);


            assign_begin    = ++begin;
            assign_cbegin   = ++cbegin;
            assign_rbegin   = ++rbegin;
            assign_crbegin  = ++crbegin;
            assert(*assign_begin == E(2, 20)    && *begin == E(2, 20));
            assert(*assign_cbegin == E(2, 20)   && *cbegin == E(2, 20));
            assert(*assign_rbegin == E(2, 20)   && *rbegin == E(2, 20));
            assert(*assign_crbegin == E(2, 20)  && *crbegin == E(2, 20));
            assert(assign_begin->m_key == 2     && assign_begin->m_value == 20      && begin->m_key == 2    && begin->m_value == 20);
            assert(assign_cbegin->m_key == 2    && assign_cbegin->m_value == 20     && cbegin->m_key == 2   && cbegin->m_value == 20);
            assert(assign_rbegin->m_key == 2    && assign_rbegin->m_value == 20     && rbegin->m_key == 2   && rbegin->m_value == 20);
            assert(assign_crbegin->m_key == 2   && assign_crbegin->m_value == 20    && crbegin->m_key == 2  && crbegin->m_value == 20);

            assign_begin    = ++begin;
            assign_cbegin   = ++cbegin;
            assign_rbegin   = ++rbegin;
            assign_crbegin  = ++crbegin;
            assert(*assign_begin == E(3, 30)    && *begin == E(3, 30));
            assert(*assign_cbegin == E(3, 30)   && *cbegin == E(3, 30));
            assert(*assign_rbegin == E(1, 10)   && *rbegin == E(1, 10));
            assert(*assign_crbegin == E(1, 10)  && *crbegin == E(1, 10));
            assert(assign_begin->m_key == 3     && assign_begin->m_value == 30      && begin->m_key == 3    && begin->m_value == 30);
            assert(assign_cbegin->m_key == 3    && assign_cbegin->m_value == 30     && cbegin->m_key == 3   && cbegin->m_value == 30);
            assert(assign_rbegin->m_key == 1    && assign_rbegin->m_value == 10     && rbegin->m_key == 1   && rbegin->m_value == 10);
            assert(assign_crbegin->m_key == 1   && assign_crbegin->m_value == 10    && crbegin->m_key == 1  && crbegin->m_value == 10);

            assign_begin    = --begin;
            assign_cbegin   = --cbegin;
            assign_rbegin   = --rbegin;
            assign_crbegin  = --crbegin;
            assert(*assign_begin == E(2, 20)    && *begin == E(2, 20));
            assert(*assign_cbegin == E(2, 20)   && *cbegin == E(2, 20));
            assert(*assign_rbegin == E(2, 20)   && *rbegin == E(2, 20));
            assert(*assign_crbegin == E(2, 20)  && *crbegin == E(2, 20));
            assert(assign_begin->m_key == 2     && assign_begin->m_value == 20      && begin->m_key == 2    && begin->m_value == 20);
            assert(assign_cbegin->m_key == 2    && assign_cbegin->m_value == 20     && cbegin->m_key == 2   && cbegin->m_value == 20);
            assert(assign_rbegin->m_key == 2    && assign_rbegin->m_value == 20     && rbegin->m_key == 2   && rbegin->m_value == 20);
            assert(assign_crbegin->m_key == 2   && assign_crbegin->m_value == 20    && crbegin->m_key == 2  && crbegin->m_value == 20);

            assign_begin    = --begin;
            assign_cbegin   = --cbegin;
            assign_rbegin   = --rbegin;
            assign_crbegin  = --crbegin;
            assert(*assign_begin == E(1, 10)    && *begin == E(1, 10));
            assert(*assign_cbegin == E(1, 10)   && *cbegin == E(1, 10));
            assert(*assign_rbegin == E(3, 30)   && *rbegin == E(3, 30));
            assert(*assign_crbegin == E(3, 30)  && *crbegin == E(3, 30));
            assert(assign_begin->m_key == 1     && assign_begin->m_value == 10      && begin->m_key == 1    && begin->m_value == 10);
            assert(assign_cbegin->m_key == 1    && assign_cbegin->m_value == 10     && cbegin->m_key == 1   && cbegin->m_value == 10);
            assert(assign_rbegin->m_key == 3    && assign_rbegin->m_value == 30     && rbegin->m_key == 3   && rbegin->m_value == 30);
            assert(assign_crbegin->m_key == 3   && assign_crbegin->m_value == 30    && crbegin->m_key == 3  && crbegin->m_value == 30);



            assign_begin    = begin++;
            assign_cbegin   = cbegin++;
            assign_rbegin   = rbegin++;
            assign_crbegin  = crbegin++;
            assert(*assign_begin == E(1, 10)    && *begin == E(2, 20));
            assert(*assign_cbegin == E(1, 10)   && *cbegin == E(2, 20));
            assert(*assign_rbegin == E(3, 30)   && *rbegin == E(2, 20));
            assert(*assign_crbegin == E(3, 30)  && *crbegin == E(2, 20));
            assert(assign_begin->m_key == 1     && assign_begin->m_value == 10      && begin->m_key == 2    && begin->m_value == 20);
            assert(assign_cbegin->m_key == 1    && assign_cbegin->m_value == 10     && cbegin->m_key == 2   && cbegin->m_value == 20);
            assert(assign_rbegin->m_key == 3    && assign_rbegin->m_value == 30     && rbegin->m_key == 2   && rbegin->m_value == 20);
            assert(assign_crbegin->m_key == 3   && assign_crbegin->m_value == 30    && crbegin->m_key == 2  && crbegin->m_value == 20);

            assign_begin    = begin++;
            assign_cbegin   = cbegin++;
            assign_rbegin   = rbegin++;
            assign_crbegin  = crbegin++;
            assert(*assign_begin == E(2, 20)    && *begin == E(3, 30));
            assert(*assign_cbegin == E(2, 20)   && *cbegin == E(3, 30));
            assert(*assign_rbegin == E(2, 20)   && *rbegin == E(1, 10));
            assert(*assign_crbegin == E(2, 20)  && *crbegin == E(1, 10));
            assert(assign_begin->m_key == 2     && assign_begin->m_value == 20      && begin->m_key == 3    && begin->m_value == 30);
            assert(assign_cbegin->m_key == 2    && assign_cbegin->m_value == 20     && cbegin->m_key == 3   && cbegin->m_value == 30);
            assert(assign_rbegin->m_key == 2    && assign_rbegin->m_value == 20     && rbegin->m_key == 1   && rbegin->m_value == 10);
            assert(assign_crbegin->m_key == 2   && assign_crbegin->m_value == 20    && crbegin->m_key == 1  && crbegin->m_value == 10);

            assign_begin    = begin--;
            assign_cbegin   = cbegin--;
            assign_rbegin   = rbegin--;
            assign_crbegin  = crbegin--;
            assert(*assign_begin == E(3, 30)    && *begin == E(2, 20));
            assert(*assign_cbegin == E(3, 30)   && *cbegin == E(2, 20));
            assert(*assign_rbegin == E(1, 10)   && *rbegin == E(2, 20));
            assert(*assign_crbegin == E(1, 10)  && *crbegin == E(2, 20));
            assert(assign_begin->m_key == 3     && assign_begin->m_value == 30      && begin->m_key == 2    && begin->m_value == 20);
            assert(assign_cbegin->m_key == 3    && assign_cbegin->m_value == 30     && cbegin->m_key == 2   && cbegin->m_value == 20);
            assert(assign_rbegin->m_key == 1    && assign_rbegin->m_value == 10     && rbegin->m_key == 2   && rbegin->m_value == 20);
            assert(assign_crbegin->m_key == 1   && assign_crbegin->m_value == 10    && crbegin->m_key == 2  && crbegin->m_value == 20);

            assign_begin    = begin--;
            assign_cbegin   = cbegin--;
            assign_rbegin   = rbegin--;
            assign_crbegin  = crbegin--;
            assert(*assign_begin == E(2, 20)    && *begin == E(1, 10));
            assert(*assign_cbegin == E(2, 20)   && *cbegin == E(1, 10));
            assert(*assign_rbegin == E(2, 20)   && *rbegin == E(3, 30));
            assert(*assign_crbegin == E(2, 20)  && *crbegin == E(3, 30));
            assert(assign_begin->m_key == 2     && assign_begin->m_value == 20      && begin->m_key == 1    && begin->m_value == 10);
            assert(assign_cbegin->m_key == 2    && assign_cbegin->m_value == 20     && cbegin->m_key == 1   && cbegin->m_value == 10);
            assert(assign_rbegin->m_key == 2    && assign_rbegin->m_value == 20     && rbegin->m_key == 3   && rbegin->m_value == 30);
            assert(assign_crbegin->m_key == 2   && assign_crbegin->m_value == 20    && crbegin->m_key == 3  && crbegin->m_value == 30);

        }

        

        //Iterator operator==
        //Iterator operator!=
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            auto begin{h.begin()};
            auto cbegin{h.cbegin()};
            auto rbegin{h.rbegin()};
            auto crbegin{h.crbegin()};
            auto end{h.end()};
            auto cend{h.cend()};
            auto rend{h.rend()};
            auto crend{h.crend()};

            assert(begin == cbegin);
            assert(rbegin == crbegin);
            assert(end == cend);
            assert(rend == crend);

            assert(begin != end);
            assert(rbegin != rend);

            H::Iterator iter{rend};        //rend
            assert(iter != begin);
            assert(iter != cbegin);
            assert(iter != rbegin);
            assert(iter != crbegin);
            //assert(iter != end);          [begin, end]범위를 벗어났으므로 정의되지 않은 영역입니다.
            //assert(iter != cend);         [begin, end]범위를 벗어났으므로 정의되지 않은 영역입니다.
            assert(iter == rend);
            assert(iter == crend);

            ++iter;                 //1
            assert(iter == begin);
            assert(iter == cbegin);
            assert(iter != rbegin);
            assert(iter != crbegin);
            assert(iter != end);
            assert(iter != cend);
            assert(iter != rend);
            assert(iter != crend);

            ++iter;                 //2
            assert(iter != begin);
            assert(iter != cbegin);
            assert(iter != rbegin);
            assert(iter != crbegin);
            assert(iter != end);
            assert(iter != cend);
            assert(iter != rend);
            assert(iter != crend);

            ++iter;                 //3
            assert(iter != begin);
            assert(iter != cbegin);
            assert(iter == rbegin);
            assert(iter == crbegin);
            assert(iter != end);
            assert(iter != cend);
            assert(iter != rend);
            assert(iter != crend);

            ++iter;                 //end
            assert(iter != begin);
            assert(iter != cbegin);
            assert(iter != rbegin);
            assert(iter != crbegin);
            assert(iter == end);
            assert(iter == cend);
            //assert(iter != rend);             [rbegin, rend]범위를 벗어났으므로 정의되지 않은 영역입니다.
            //assert(iter != crend);            [rbegin, rend]범위를 벗어났으므로 정의되지 않은 영역입니다.

        }

        //Iterator foreach
        {

            H           h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            const H&    ch{h};

            for(auto& e : h){ assert(h.exists(e)); }        //e는 중복되는 값이 없기 때문에 모든 e에 대해 같은 원소가 존재하면 모든 원소를 순회한 것입니다.
            for(const auto& e : ch){ assert(h.exists(e)); }
            for(auto& e : MIHYIterator_ForEach_Reverse<H>(h)){ assert(h.exists(e)); }
            for(const auto& e : MIHYIterator_ForEach_Reverse<const H>(ch)){ assert(h.exists(e)); }

        }

        //Iterator 생성자(복사 생성자)
        //Iterator 생성자(이동 생성자)
        //Iterator 생성자(반복자)
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            auto begin{h.begin()};
            auto cbegin{h.cbegin()};
            auto rbegin{h.rbegin()};
            auto crbegin{h.crbegin()};
            auto end{h.end()};
            auto cend{h.cend()};
            auto rend{h.rend()};
            auto crend{h.crend()};

            H::Iterator copy{begin};
            H::Iterator ccopy{cbegin};
            H::Iterator rcopy{rbegin};
            H::Iterator crcopy{crbegin};
            assert(copy == begin);
            assert(ccopy == cbegin);
            assert(rcopy == rbegin);
            assert(crcopy == crbegin);

            H::Iterator move{std::move(copy)};
            H::Iterator cmove{std::move(ccopy)};
            H::Iterator rmove{std::move(rcopy)};
            H::Iterator crmove{std::move(crcopy)};
            assert(move == begin);
            assert(cmove == cbegin);
            assert(rmove == rbegin);
            assert(crmove == crbegin);

            H::Iterator iter_copy_iter{begin};
            H::Iterator iter_copy_citer{cbegin};
            H::Iterator iter_copy_riter{rbegin};
            H::Iterator iter_copy_criter{crbegin};
            assert(iter_copy_iter == begin);
            assert(iter_copy_citer == cbegin);
            assert(iter_copy_riter == rbegin);
            assert(iter_copy_criter == crbegin);

            H::Const_Iterator citer_copy_iter{begin};
            H::Const_Iterator citer_copy_citer{cbegin};
            H::Const_Iterator citer_copy_riter{rbegin};
            H::Const_Iterator citer_copy_criter{crbegin};
            assert(citer_copy_iter == begin);
            assert(citer_copy_citer == cbegin);
            assert(citer_copy_riter == rbegin);
            assert(citer_copy_criter == crbegin);

            H::Reverse_Iterator riter_copy_iter{begin};
            H::Reverse_Iterator riter_copy_citer{cbegin};
            H::Reverse_Iterator riter_copy_riter{rbegin};
            H::Reverse_Iterator riter_copy_criter{crbegin};
            assert(riter_copy_iter == begin);
            assert(riter_copy_citer == cbegin);
            assert(riter_copy_riter == rbegin);
            assert(riter_copy_criter == crbegin);

            H::Const_Reverse_Iterator criter_copy_iter{begin};
            H::Const_Reverse_Iterator criter_copy_citer{cbegin};
            H::Const_Reverse_Iterator criter_copy_riter{rbegin};
            H::Const_Reverse_Iterator criter_copy_criter{crbegin};
            assert(criter_copy_iter == begin);
            assert(criter_copy_citer == cbegin);
            assert(criter_copy_riter == rbegin);
            assert(criter_copy_criter == crbegin);

        }

        //생성자(기본)
        {

            H h{hash};
            assert(h.get_size() == 0);          //생성자 호출이 문제가 없는지

            h.insert(E{1, 10});                //생성자 호출 후 사용해도 문제가 없는지
            assert(h.get_size() == 1);
            CHECK_ELEMENT(h, 1, 10);

        }

        //생성자(초기화 리스트)
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            h.insert(E{4, 40});                //생성자 호출 후 사용해도 문제가 없는지
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

        }

        //생성자(복사 생성자)
        {

            H lvalue{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            H h{lvalue};
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            assert(lvalue.get_size() == 3);
            CHECK_ELEMENT(lvalue, 1, 10);
            CHECK_ELEMENT(lvalue, 2, 20);
            CHECK_ELEMENT(lvalue, 3, 30);

            h.insert(E{4, 40});          //생성자 호출 후 사용해도 문제가 없는지
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

            assert(lvalue.get_size() == 3);
            CHECK_ELEMENT(lvalue, 1, 10);
            CHECK_ELEMENT(lvalue, 2, 20);
            CHECK_ELEMENT(lvalue, 3, 30);

        }

        //생성자(이동 생성자)
        {

            H rvalue{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};
            H h{std::move(rvalue)};
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            assert(rvalue.get_size() == 0);

            h.insert(E{4, 40});          //생성자 호출 후 사용해도 문제가 없는지
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

            assert(rvalue.get_size() == 0);

        }

        //생성자(반복자)
        {

            MIHYList<E> l{E{1, 10}, E{2, 20}, E{3, 30}};

            H h{hash, l.begin(), l.end()};
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            h.insert(E{4, 40});                //생성자 호출 후 사용해도 문제가 없는지
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

        }

        //operator=(초기화 리스트)
        {

            H h{hash};

            h = {E{1, 10}, E{2, 20}};                           //빈 해시맵에 대입하는 경우
            assert(h.get_size() == 2);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);

            h.insert(E{3, 30});                                 //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            h = {E{1, 10}, E{2, 20}, E{3, 30}, E{4, 40}};       //이미 원소가 있는 해시맵에 대입하는 경우
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

            h.insert(E{5, 50});                                 //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 5);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);
            CHECK_ELEMENT(h, 5, 50);

        }

        //operator=(복사)
        {

            auto hash2{[](const E& e){return e.m_key * 5;}};

            H lvalue0{hash2, {E{1, 10}, E{2, 20}}};
            H lvalue1{hash2, {E{1, 10}, E{2, 20}, E{3, 30}, E{4, 40}}};
            H h{hash};

            h = lvalue0;                    //빈 해시맵에 대입하는 경우
            assert(h.get_size() == 2);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);

            assert(lvalue0.get_size() == 2);
            CHECK_ELEMENT(lvalue0, 1, 10);
            CHECK_ELEMENT(lvalue0, 2, 20);

            h.insert(E{3, 30});             //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            assert(lvalue0.get_size() == 2);
            CHECK_ELEMENT(lvalue0, 1, 10);
            CHECK_ELEMENT(lvalue0, 2, 20);

            h = lvalue1;                    //이미 원소가 있는 해시맵에 대입하는 경우
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

            assert(lvalue1.get_size() == 4);
            CHECK_ELEMENT(lvalue1, 1, 10);
            CHECK_ELEMENT(lvalue1, 2, 20);
            CHECK_ELEMENT(lvalue1, 3, 30);
            CHECK_ELEMENT(lvalue1, 4, 40);

            h.insert(E{5, 50});             //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 5);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);
            CHECK_ELEMENT(h, 5, 50);

            assert(lvalue1.get_size() == 4);
            CHECK_ELEMENT(lvalue1, 1, 10);
            CHECK_ELEMENT(lvalue1, 2, 20);
            CHECK_ELEMENT(lvalue1, 3, 30);
            CHECK_ELEMENT(lvalue1, 4, 40);

        }

        //operator=(이동)
        {

            auto hash2{[](const E& e){return e.m_key * 5;}};

            H lvalue0{hash2, {E{1, 10}, E{2, 20}}};
            H lvalue1{hash2, {E{1, 10}, E{2, 20}, E{3, 30}, E{4, 40}}};
            H h{hash};

            h = std::move(lvalue0);                     //빈 해시맵에 대입하는 경우
            assert(h.get_size() == 2);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);

            assert(lvalue0.get_size() == 0);

            h.insert(E{3, 30});                         //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 3);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            assert(lvalue0.get_size() == 0);

            h = std::move(lvalue1);                     //이미 원소가 있는 해시맵에 대입하는 경우
            assert(h.get_size() == 4);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);

            assert(lvalue1.get_size() == 0);

            h.insert(E{5, 50});                         //대입 후 사용해도 문제가 없는지
            assert(h.get_size() == 5);
            CHECK_ELEMENT(h, 1, 10);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);
            CHECK_ELEMENT(h, 4, 40);
            CHECK_ELEMENT(h, 5, 50);

            assert(lvalue1.get_size() == 0);
        }
        

        //insert
        {

            E                           lvalue0{1, 10};
            E                           rvalue0{2, 20};
            std::initializer_list<E>    initializer_list0{{3, 30}, {4, 40}};
            H                           copy0{hash, {E{5, 50}, E{6, 60}}};
            MIHYList<E>                 list0{E{7, 70}, E{8, 80}};
            H                           h{hash};

            h.insert(lvalue0);
            h.insert(std::move(rvalue0));
            h.insert(initializer_list0);
            h.insert(copy0);
            h.insert(list0.begin(), list0.end());
            assert(h.get_size() == 8);
            for(UInt64 i = 1; i <= 8; ++i){
                CHECK_ELEMENT(h, i, i * 10);
            }

            //충돌하는 값을 넣었을 경우. 여러 원소를 집어넣는 경우에는 충돌되는 경우와 아닌 경우를 섞습니다.
            std::initializer_list<E>    initializer_list1{{3, 30}, {4, 40}, {9, 90}};
            H                           copy1{hash, {E{5, 50}, E{6, 60}, E{10, 100}}};
            MIHYList<E>                 list1{E{7, 70}, E{8, 80}, E{11, 110}};

            h.insert(lvalue0);
            h.insert(rvalue0);
            h.insert(initializer_list1);
            h.insert(copy1);
            h.insert(list1.begin(), list1.end());
            assert(h.get_size() == 11);
            for(UInt64 i = 1; i <= 11; ++i){
                CHECK_ELEMENT(h, i, i * 10);
            }


        }

        //delete
        {

            H h{hash, {E{1, 10}, E{2, 20}, E{3, 30}}};

            
            assert(!h.erase(E{4, 10}));         //존재하지 않는 원소를 지우려고 할 때
            assert(!h.erase(E{5, 20}));

            assert(h.erase(E{1, 10}));          //존재하는 원소를 지우려고 할 때
            assert(h.get_size() == 2);
            CHECK_ELEMENT(h, 2, 20);
            CHECK_ELEMENT(h, 3, 30);

            assert(h.erase(E{2, 20}));
            assert(h.get_size() == 1);
            CHECK_ELEMENT(h, 3, 30);

            assert(h.erase(E{3, 30}));
            assert(h.get_size() == 0);

            assert(!h.erase(E{1, 10}));         //존재하지 않는 원소를 지우려고 할 때
            assert(!h.erase(E{2, 10}));
            assert(!h.erase(E{3, 10}));
            assert(!h.erase(E{4, 10}));
            assert(!h.erase(E{5, 20}));

        }

        //find
        {

            H h{hash, {E{2, 20}, {3, 30}, {4, 40}}};
            E temp{};

            assert(!h.find(E{1, 10}, &temp));
            assert(h.find(E{2, 20}, &temp) && temp.m_key == 2 && temp.m_value == 20);
            assert(h.find(E{3, 30}, &temp) && temp.m_key == 3 && temp.m_value == 30);
            assert(h.find(E{4, 40}, &temp) && temp.m_key == 4 && temp.m_value == 40);
            assert(!h.find(E{5, 50}, &temp));

        }

        //exists
        {

            H h{hash, {E{2, 20}, {3, 30}, {4, 40}}};

            assert(!h.exists(E{1, 10}));
            assert(h.exists(E{2, 20}));
            assert(h.exists(E{3, 30}));
            assert(h.exists(E{4, 40}));
            assert(!h.exists(E{5, 50}));

        }

    }

    }
}