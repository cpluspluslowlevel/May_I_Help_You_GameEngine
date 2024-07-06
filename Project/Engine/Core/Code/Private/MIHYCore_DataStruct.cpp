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

        bool operator==(const List_Element& v){
            return value == v.value;
        }

        bool operator==(Int64 v){
            return value == v;
        }

        bool operator!=(Int64 v){
            return value != v;
        }

    };

    void mihylist_unittest_copy_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list);
    void mihylist_unittest_push_back_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list);
    void mihylist_unittest(){

        

        using E = List_Element;
        using L = MIHYList<E>;

        //get_size
        {
            L l{{E{10}, E{20}, E{30}}};
            assert(l.get_size() == 3);
        }

        //clear
        {
            L l{{E{10}, E{20}, E{30}}};
            assert(l.get_size() == 3);
            l.clear();
            assert(l.get_size() == 0);
            assert(l.m_head == nullptr);
            assert(l.m_tail == nullptr);
        }

        //get
        {
            L l{{E{10}, E{20}, E{30}}};
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
        }

        //생성자
        {
            L l{};
            assert(l.get_size() == 0);
        }

        //생성자(초기화 리스트)
        {
            L l{E{10}, E{20}, E{30}};
            assert(l.get_size() == 3);
            assert(l.get(0) == 10);
            assert(l.get(1) == 20);
            assert(l.get(2) == 30);
            assert(l.m_head->value == 10);
            assert(l.m_tail->value == 30);
            assert(l.m_head->next->value == 20);
            assert(l.m_tail->prev->value == 20);
            assert(l.m_head->next->prev == l.m_head);
            assert(l.m_head->next->next == l.m_tail);

            L l2{{E{10}}};              //원소가 하나인 경우
            assert(l2.get_size() == 1);
            assert(l2.get(0) == 10);
            assert(l2.m_head == l2.m_tail);
            assert(l2.m_head->prev == nullptr);
            assert(l2.m_head->next == nullptr);

            L l3{{}};                   //원소가 없는 경우
            assert(l3.get_size() == 0);
            assert(l3.m_head == nullptr);
            assert(l3.m_tail == nullptr);

        }

        //생성자(복사)
        {
            L l{E{10}, E{20}, E{30}};
            L copy{l};
            assert(l.get_size() == 3);
            assert(l.get(0) == 10 && l.get(1) == 20 && l.get(2) == 30);
            assert(copy.get_size() == 3);
            assert(copy.get(0) == 10 && copy.get(1) == 20 && copy.get(2) == 30);
        }

        //생성자(이동)
        {
            L l{E{10}, E{20}, E{30}};
            L move{std::move(l)};
            assert(l.get_size() == 0);
            assert(move.get_size() == 3);
            assert(move.get(0) == 10 && move.get(1) == 20 && move.get(2) == 30);
        }

        //대입
        {
            //빈 컨테이너에 대입되는 경우
            #define f mihylist_unittest_copy_test
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

        //이동
        {
            L l{E{10}, E{20}, E{30}};
            L move{};
            move = std::move(l);
            assert(l.get_size() == 0);
            assert(move.get_size() == 3);
            assert(move.get(0) == 10 && move.get(1) == 20 && move.get(2) == 30);
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
            mihylist_unittest_push_back_test({}, {});                                           //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_test({}, {E{10}});                                      //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_test({}, {E{10}, E{20}});                               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_test({}, {E{10}, E{20}, E{30}});                        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head == m_tail인 리스트인 경우
            mihylist_unittest_push_back_test({E{1}}, {});                                       //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_test({E{1}}, {E{10}});                                  //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_test({E{1}}, {E{10}, E{20}});                           //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_test({E{1}}, {E{10}, E{20}, E{30}});                    //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 없는 리스트인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}}, {});                                 //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}}, {E{10}});                            //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}}, {E{10}, E{20}});                     //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_test({E{1}, E{2}}, {E{10}, E{20}, E{30}});              //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

            //m_head != m_tail이고 사이에 노드가 있는 리스트인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}, E{3}}, {});                           //복사 대상이 빈 리스트인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}, E{3}}, {E{10}});                      //복사 대상의 m_head == m_tail인 경우
            mihylist_unittest_push_back_test({E{1}, E{2}, E{3}}, {E{10}, E{20}});               //복사 대상의 m_head != m_tail이고 사이에 노드가 없는 경우
            mihylist_unittest_push_back_test({E{1}, E{2}, E{3}}, {E{10}, E{20}, E{30}});        //복사 대상의 m_head != m_tail이고 사이에 노드가 있는 경우

        }
        
        //push_back(List rvalue)
        {

        }
        //push_back(Iterator)
        {

        }
        
        

        //push_front(lvalue)
        //push_front(rvalue)
        //push_front(초기화 리스트)
        //push_front(List lvalue)
        //push_front(List rvalue)
        //push_front(Iterator)

        //push(Index, lvalue)
        //push(Index, rvalue)
        //push(Index, 초기화 리스트)
        //push(Index, List lvalue)
        //push(Index, List rvalue)
        //push(Index, Iterator)
        //push(Iterator, lvalue)
        //push(Iterator, rvalue)
        //push(Iterator, 초기화 리스트)
        //push(Iterator, List lvalue)
        //push(Iterator, List rvalue)
        //push(Iterator, Iterator)

        //pop_back

        //pop_front

        //Iterator 생성자

        //Iterator


    }

    void mihylist_unittest_copy_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> copy_list){

        MIHYList<List_Element> copy{copy_list};
        MIHYList<List_Element> l{list};

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

    void mihylist_unittest_push_back_test(std::initializer_list<List_Element> list, std::initializer_list<List_Element> push_back_list){

        MIHYList<List_Element> l{list};

        for(auto& e : push_back_list){
            l.push_back(e);
        }

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
            assert(l.get_head_node() == nullptr);
            assert(l.get_tail_node() == nullptr);
        }

    }


    }
}