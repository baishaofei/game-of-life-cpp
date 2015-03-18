#ifndef LSJKDFP_5783762_VNBQAAAW_789657_FYETTIWENCHWS
#define LSJKDFP_5783762_VNBQAAAW_789657_FYETTIWENCHWS

#define ABSTRACT(...) virtual __VA_ARGS__ = 0
#define OVERRIDE(...) virtual __VA_ARGS__
#define EXTENDS(...) , ##__VA_ARGS__
#define IMPLEMENTS(...) EXTENDS(__VA_ARGS__)

 namespace details
 {
     template <typename T>
     struct Role
     {
         virtual ~Role() {}
     };
 }

 #define DEFINE_ROLE(type) struct type : ::details::Role<type>

#endif
