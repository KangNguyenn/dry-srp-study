# Báo cáo: DRY và SRP — Sử dụng một cách hợp lý

> **Trạng thái tài liệu:** bản nháp học tập dựa trên yêu cầu bài tập. Cần đọc lại mã nguồn, điều chỉnh cách diễn đạt và cá nhân hóa phần đánh giá trước khi nộp.  
> **Ngôn ngữ mã nguồn:** C++17.

## 1. Giới thiệu

Trong quá trình phát triển phần mềm, yêu cầu thường xuyên thay đổi. Một chương trình có thể đang chạy đúng nhưng vẫn khó bảo trì nếu cùng một quy tắc được viết ở nhiều nơi hoặc một lớp phải thay đổi vì nhiều nguyên nhân không liên quan.

DRY (*Don't Repeat Yourself*) và SRP (*Single Responsibility Principle*) là hai nguyên tắc giúp tổ chức mã nguồn để dễ hiểu và dễ thay đổi hơn. Tuy nhiên, chúng không phải mệnh lệnh phải làm theo một cách máy móc. Loại bỏ mọi đoạn mã trông giống nhau có thể tạo ra một abstraction phức tạp; tách mọi phương thức thành một lớp riêng có thể làm chương trình phân mảnh và khó theo dõi.

Báo cáo này trình bày ý nghĩa cơ bản của DRY và SRP, phân tích những tình huống áp dụng quá mức, rồi đánh giá năm tình huống Code Review trong đề bài. Các ví dụ C++ tương ứng được lưu trong thư mục `src/`.

## 2. Nghiên cứu cơ bản: DRY và SRP

### 2.1. DRY là gì?

DRY là viết tắt của *Don't Repeat Yourself*. Theo cách diễn đạt trong *The Pragmatic Programmer*, mỗi phần kiến thức trong hệ thống nên có một biểu diễn có thẩm quyền, rõ ràng và không mơ hồ [1]. Vì vậy, DRY không chỉ có nghĩa là không sao chép và dán các dòng mã. Trọng tâm của nguyên tắc là tránh việc cùng một kiến thức, ý định hoặc quy tắc phải được duy trì ở nhiều nơi.

Ví dụ, nếu hai chức năng cùng kiểm tra một chính sách hợp lệ của khách hàng nhưng mỗi chức năng tự viết một bản kiểm tra riêng, chúng đang lưu giữ cùng một quy tắc ở hai vị trí. Khi chính sách thay đổi, lập trình viên phải tìm và sửa cả hai nơi. Nếu chỉ sửa một nơi, hai chức năng có thể đưa ra kết quả khác nhau dù đáng lẽ phải tuân theo cùng một chính sách.

### 2.2. Những dạng lặp lại có thể xuất hiện

Một số dạng thường gặp:

- **Lặp mã nguồn:** cùng một đoạn kiểm tra, tính toán hoặc xử lý lỗi xuất hiện ở nhiều hàm.
- **Lặp quy tắc nghiệp vụ:** một chính sách như điều kiện hợp lệ, mức phí hoặc giới hạn được định nghĩa ở nhiều module.
- **Lặp dữ liệu/cấu hình:** cùng một giá trị quan trọng được khai báo ở nhiều nơi và có nguy cơ không đồng bộ.
- **Lặp cấu trúc hoặc quy trình:** nhiều phần của chương trình phải thực hiện cùng một chuỗi thao tác.
- **Lặp tài liệu:** hướng dẫn hoặc mô tả một quy tắc được sao chép ở nhiều tài liệu, sau đó chỉ một bản được cập nhật.

Không phải mọi đoạn mã có hình thức giống nhau đều là lặp lại cùng một kiến thức. Hai phép tính có cùng công thức tại thời điểm hiện tại có thể đại diện cho hai chính sách độc lập. Vì vậy, phải xem xét ý nghĩa và nguyên nhân thay đổi trước khi hợp nhất chúng.

### 2.3. Vì sao lặp logic gây khó khăn khi yêu cầu thay đổi?

Giả sử chương trình có hai chức năng đăng ký và cập nhật khách hàng. Cả hai đều kiểm tra tên không được để trống và email phải chứa ký tự `@`. Nếu chính sách email sau này thay đổi, lập trình viên phải nhớ cập nhật hai đoạn kiểm tra.

Vấn đề không chỉ là tốn thêm thao tác. Nó còn tạo ra các rủi ro:

1. Một bản sao được sửa nhưng bản còn lại bị bỏ sót.
2. Hai bản sao dần có hành vi khác nhau mà không có chủ đích.
3. Người bảo trì phải tìm kiếm trên nhiều vị trí để hiểu một quy tắc duy nhất.
4. Kiểm thử phải bảo đảm nhiều bản triển khai vẫn đồng nhất.

### 2.4. Những cách giảm sự lặp lại

Có thể lựa chọn cách xử lý tùy loại kiến thức:

- Đưa logic ổn định, được dùng nhiều nơi vào một hàm có tên rõ nghĩa.
- Đóng gói một chính sách nghiệp vụ dùng chung vào một thành phần có trách nhiệm phù hợp.
- Đưa giá trị cấu hình chung về một nguồn cấu hình có thẩm quyền.
- Dùng kiểu dữ liệu hoặc schema chung khi các module thực sự chia sẻ cùng một mô hình.
- Sinh mã hoặc tài liệu từ một nguồn dữ liệu duy nhất khi có nhu cầu phù hợp.
- Bổ sung kiểm thử để phát hiện các bản triển khai không còn nhất quán.

Không nên tạo abstraction chỉ để giảm số dòng. Thành phần dùng chung cần có tên diễn đạt đúng ý nghĩa và ranh giới thay đổi hợp lý.

### 2.5. Ví dụ DRY: kiểm tra khách hàng bị lặp

Trong [`validation_before.cpp`](src/dry/validation_before.cpp), hai thao tác đăng ký và cập nhật chứa cùng một điều kiện kiểm tra. Phiên bản [`validation_after.cpp`](src/dry/validation_after.cpp) đưa điều kiện đó về hàm `isValidCustomer()`, sau đó cả hai thao tác gọi chung.

Thiết kế sau tốt hơn trong bối cảnh hai thao tác thực sự tuân theo cùng một chính sách khách hàng. Khi chính sách đổi, chỉ cần sửa một nơi. Hàm dùng chung cũng có thể được kiểm thử độc lập.

## 3. SRP — Nguyên tắc đơn nhiệm

### 3.1. SRP là gì?

SRP là viết tắt của *Single Responsibility Principle*. Robert C. Martin diễn đạt ý tưởng cốt lõi là: tập hợp những thứ thay đổi vì cùng một lý do và tách riêng những thứ thay đổi vì các lý do khác nhau [2].

Cụm từ thường được dùng để giải thích SRP là một lớp chỉ nên có **một lý do để thay đổi** (*one reason to change*). Điều này không có nghĩa một lớp chỉ được viết một phương thức. Nó có nghĩa những hành vi trong lớp nên thuộc về một trách nhiệm có tính gắn kết, thay vì tập hợp các công việc độc lập chỉ vì chúng cùng thao tác trên một đối tượng dữ liệu.

### 3.2. Trách nhiệm của lớp hoặc module là gì?

Trách nhiệm là nhóm hành vi và quy tắc mà lớp/module chịu trách nhiệm duy trì. Có thể nhận biết trách nhiệm thông qua câu hỏi: yêu cầu từ đâu có thể khiến thành phần này phải thay đổi?

Ví dụ, một lớp `OrderService` vừa kiểm tra quy tắc đặt hàng, vừa tính tiền, vừa lưu cơ sở dữ liệu, vừa gửi email. Những công việc đó có thể thay đổi vì các nguyên nhân khác nhau:

- Chính sách đặt hàng thay đổi.
- Cách tính giá hoặc khuyến mãi thay đổi.
- Cấu trúc cơ sở dữ liệu thay đổi.
- Mẫu email hoặc nhà cung cấp gửi thư thay đổi.

Khi tất cả nằm trong một lớp, thay đổi ở một mảng có thể khiến lớp phải sửa và có thể ảnh hưởng đến các mảng còn lại.

### 3.3. Dấu hiệu một lớp có thể đang vi phạm SRP

Một lớp đáng được xem xét khi:

- Nó phục vụ nhiều nhóm yêu cầu hoặc chính sách khác nhau.
- Nó trộn lẫn nghiệp vụ, lưu trữ dữ liệu, giao tiếp mạng và trình bày.
- Một thay đổi nhỏ ở một chức năng khiến nhiều chức năng không liên quan phải kiểm thử lại.
- Tên lớp quá chung chung nhưng chứa nhiều nhóm phương thức ít liên quan.
- Các phương thức có thể được tách thành các nhóm thay đổi độc lập mà không làm mất ý nghĩa của mô hình.

Đây là dấu hiệu để xem xét, không phải bằng chứng tự động. Cần xem bối cảnh và cách thành phần được sử dụng.

### 3.4. Cách tách trách nhiệm

Có thể tách theo các nguyên nhân thay đổi:

- Bộ kiểm tra chịu trách nhiệm xác định đơn hàng có hợp lệ không.
- Bộ tính toán chịu trách nhiệm tính tổng tiền.
- Repository chịu trách nhiệm lưu và truy xuất dữ liệu.
- Thành phần thông báo chịu trách nhiệm gửi email.
- Service ở tầng điều phối có thể gọi các thành phần trên theo đúng trình tự.

Sau khi tách, lớp điều phối vẫn có thể gọi nhiều phương thức. Điều đó không tự động vi phạm SRP, bởi trách nhiệm của nó có thể là điều phối quy trình đặt hàng.

### 3.5. Ví dụ SRP: OrderService

Trong [`order_service_before.cpp`](src/srp/order_service_before.cpp), một lớp vừa xác thực, tính tổng tiền, lưu đơn hàng và gửi xác nhận. Trong [`order_service_after.cpp`](src/srp/order_service_after.cpp), các công việc được chuyển sang `OrderValidator`, `OrderCalculator`, `OrderRepository` và `ConfirmationSender`.

Lớp `OrderService` vẫn tồn tại, nhưng nó chỉ điều phối quy trình. Thiết kế này có ích khi các phần trên có khả năng thay đổi độc lập hoặc cần được kiểm thử, thay thế riêng. Với chương trình cực nhỏ hoặc các phần không có khả năng thay đổi độc lập, việc tách đầy đủ có thể không đáng với chi phí bổ sung.

## 4. Phân tích nâng cao: lạm dụng và đánh đổi

### 4.1. DRY: ít mã trùng lặp hơn có luôn tốt hơn?

**Không.** Số dòng mã trùng nhau không phải thước đo duy nhất của chất lượng thiết kế. DRY hướng đến việc không duy trì cùng một kiến thức ở nhiều nơi; nó không bắt buộc mọi biểu thức giống nhau phải được đặt trong cùng một hàm.

Cần phân biệt hai trường hợp:

- Hai đoạn mã cùng thực thi một chính sách nghiệp vụ: thay đổi chính sách cần được phản ánh đồng thời ở mọi nơi. Đây là ứng viên tốt cho logic dùng chung.
- Hai đoạn mã có cú pháp hoặc công thức giống nhau nhưng thuộc hai chính sách khác nhau: chúng có thể thay đổi độc lập và nên được giữ riêng.

Ví dụ, mô-đun thuế và mô-đun giảm giá khách hàng thân thiết hiện cùng nhân số tiền với 10%. Tuy vậy, thuế thuộc chính sách thuế, còn giảm giá thuộc chính sách kinh doanh. Khi thuế thay đổi, không có lý do tự động nào buộc mức giảm giá thay đổi theo. [`independent_rules.cpp`](src/dry/independent_rules.cpp) giữ hai phép tính riêng để thể hiện sự khác nhau về ý nghĩa đó.

### 4.2. Lạm dụng DRY và Premature Abstraction

*Premature Abstraction* là tạo ra một cấu trúc tổng quát trước khi hiểu rõ các trường hợp sử dụng thực tế và điểm chung ổn định của chúng. Lập trình viên có thể nhìn thấy hai đoạn mã hơi giống nhau rồi xây dựng một framework, nhiều interface hoặc nhiều tham số để dùng chung.

Việc này có thể tạo ra các vấn đề:

1. **Khó đọc:** người đọc phải hiểu framework trước khi hiểu phép tính đơn giản.
2. **Tăng coupling:** những thành phần vốn độc lập bị buộc phải dùng chung một abstraction.
3. **Khó sửa:** một thay đổi cục bộ có thể yêu cầu sửa abstraction tổng quát và các nơi đang sử dụng nó.
4. **Tăng chi phí bảo trì:** số lớp, interface, factory và cấu hình tăng lên nhưng lợi ích tái sử dụng không tương xứng.

[`premature_abstraction.cpp`](src/dry/premature_abstraction.cpp) minh họa một framework nhiều tầng chỉ để thực hiện phép nhân với một tỷ lệ cố định. Ví dụ này không chứng minh mọi framework đều xấu; nó cho thấy abstraction cần giải quyết một nhu cầu thật, không chỉ tồn tại để loại bỏ vài dòng mã.

### 4.3. Khi nào có thể chấp nhận trùng lặp?

Có thể giữ các đoạn mã riêng khi:

- Chúng thuộc hai chính sách hoặc hai nhóm nghiệp vụ có chủ sở hữu khác nhau.
- Chúng dự kiến thay đổi độc lập.
- Việc tạo abstraction đòi hỏi nhiều tham số, nhánh điều kiện hoặc tên khó hiểu.
- Phần trùng lặp rất nhỏ, ổn định và chi phí điều hướng sang thành phần dùng chung cao hơn lợi ích.
- Chưa có đủ thông tin để khẳng định hai đoạn mã sẽ tiếp tục cùng ý nghĩa trong tương lai.

Đây không phải giấy phép để sao chép mã tùy tiện. Khi giữ trùng lặp, nên ghi tên hàm và tên biến thể hiện rõ mục đích riêng, đồng thời kiểm thử từng chính sách.

### 4.4. SRP: mỗi trách nhiệm có cần một lớp riêng?

**Không.** SRP không quy định một lớp chỉ có một phương thức. Một lớp có thể có nhiều phương thức nếu chúng phục vụ một trách nhiệm rõ ràng và có xu hướng thay đổi cùng nhau.

Ví dụ, một lớp `StudentRecord` có thể cung cấp các thao tác cập nhật thông tin sinh viên, thêm điểm và tính GPA. Những phương thức này có thể cùng phục vụ việc quản lý một hồ sơ sinh viên. Ví dụ nằm trong [`student_cohesive.cpp`](src/srp/student_cohesive.cpp).

Ngược lại, tạo `StudentNameGetter`, `StudentNameSetter`, `StudentAgeGetter` và `StudentAgeSetter` thành bốn lớp độc lập là chia nhỏ quá mức nếu chúng chỉ bọc các thao tác đọc/ghi đơn giản. Ví dụ [`over_split_student.cpp`](src/srp/over_split_student.cpp) minh họa cách tổ chức như vậy.

### 4.5. Chi phí của việc tạo quá nhiều lớp

Tách lớp có thể giúp phân định trách nhiệm, nhưng cũng có chi phí:

- Người đọc phải di chuyển qua nhiều file để hiểu một quy trình nhỏ.
- Số lượng constructor, dependency và object cần khởi tạo tăng lên.
- Interface hoặc wrapper rỗng làm tăng tầng gián tiếp nhưng không mang lại khả năng thay thế có ý nghĩa.
- Các lớp nhỏ có thể phụ thuộc chặt chẽ vào nhau, khiến tổng thể khó thay đổi hơn.

Do đó, cần cân nhắc **cohesion** (tính gắn kết) và **coupling** (mức độ phụ thuộc). Nhóm các hành vi có liên quan và thường thay đổi cùng nhau giúp thành phần có cohesion cao. Giảm các phụ thuộc không cần thiết giữa những thành phần thay đổi vì lý do khác nhau giúp hạn chế coupling. Mục tiêu không phải giảm số lớp bằng mọi giá mà là đặt ranh giới dễ hiểu.

## 5. Code Review — Đánh giá năm tình huống

### 5.1. Kiểm tra dữ liệu dùng chung (Shared validation)

**Đánh giá: nên dùng chung logic.**

Hai thao tác kiểm tra khách hàng theo cùng một chính sách nghiệp vụ. Đây là cùng một kiến thức được sử dụng ở nhiều nơi, nên nên đưa điều kiện kiểm tra vào một hàm hoặc thành phần dùng chung.

Điều kiện quan trọng là hai nơi thực sự cần cùng chính sách và cùng cách diễn giải kết quả. Nếu một nơi có quy tắc bổ sung riêng, phần riêng đó nên được thể hiện độc lập thay vì nhồi tất cả vào một hàm tổng quát với nhiều cờ boolean.

### 5.2. Các phép tính tương tự (Similar calculations)

**Đánh giá: có thể chấp nhận giữ riêng.**

Mô-đun thuế và mô-đun giảm giá cùng một công thức ở thời điểm hiện tại, nhưng xuất phát từ hai chính sách nghiệp vụ khác nhau. Nếu thuế và giảm giá có lịch thay đổi, người quyết định và yêu cầu kiểm thử riêng, hợp nhất chỉ vì phép tính giống nhau có thể tạo ra coupling không cần thiết.

Nên giữ hai hàm với tên thể hiện rõ nghiệp vụ. Chỉ hợp nhất phần tính toán mức thấp nếu có một quy tắc chung thực sự, ổn định và abstraction không làm mất ranh giới chính sách.

### 5.3. Lớp Student có nhiều phương thức

**Đánh giá: vấn đề tiềm ẩn, cần xem ranh giới trách nhiệm.**

Cập nhật thông tin sinh viên và lưu hồ sơ có thể thuộc cùng mô hình dữ liệu. Tính GPA và kiểm tra tình trạng học tập có thể thuộc nghiệp vụ học vụ. Hiển thị thông tin tổng hợp có thể thuộc tầng trình bày hoặc báo cáo.

Nếu lớp `Student` vừa lưu trạng thái vừa chứa toàn bộ quy tắc học vụ và định dạng hiển thị, nó có nhiều lý do độc lập để thay đổi. Nên giữ dữ liệu và hành vi cốt lõi gắn với hồ sơ trong mô hình phù hợp, chuyển quy tắc học vụ sang thành phần nghiệp vụ và chuyển định dạng hiển thị sang lớp trình bày/báo cáo.

Không nên tách máy móc mọi phương thức: quyết định dựa trên việc các nhóm chức năng có thay đổi độc lập và có thể được kiểm thử riêng hay không.

### 5.4. Quá nhiều lớp getter/setter

**Đánh giá: áp dụng SRP quá mức.**

Bốn lớp chỉ để đọc/ghi tên và tuổi thường không biểu diễn bốn trách nhiệm có ý nghĩa. Chúng làm tăng số lượng file và tầng gián tiếp nhưng không tạo ra sự độc lập thực sự.

Các thao tác đọc/ghi có thể nằm trong lớp `Student` hoặc một kiểu dữ liệu hồ sơ phù hợp. Khi có quy tắc riêng phức tạp (ví dụ kiểm tra tính hợp lệ của tuổi hoặc quyền chỉnh sửa hồ sơ), khi đó mới cân nhắc tách thành phần theo trách nhiệm thật sự.

### 5.5. Dịch vụ đơn hàng (Order service)

**Đánh giá: nên xem xét tách các trách nhiệm.**

Kiểm tra đơn hàng, tính tổng tiền, lưu dữ liệu và gửi email có những nguyên nhân thay đổi khác nhau. Tách các chức năng này giúp thay đổi một phần ít ảnh hưởng phần còn lại và dễ viết kiểm thử riêng.

Tuy nhiên, `OrderService` vẫn có thể tồn tại để điều phối thứ tự: xác thực, tính tổng, lưu đơn và gửi thông báo. Không cần tách lớp điều phối nếu nhiệm vụ duy nhất của nó là điều phối quy trình đặt hàng. Cách tổ chức minh họa trong `src/srp/order_service_after.cpp`.

## 6. Đánh giá và quyết định thiết kế

DRY và SRP nên được xem là nguyên tắc định hướng, không phải quy tắc cú pháp bắt buộc. Một thiết kế tốt không nhất thiết có ít dòng mã nhất hoặc nhiều lớp nhất. Nó cần làm rõ nơi lưu giữ kiến thức, lý do thay đổi và các phụ thuộc giữa thành phần.

Trước khi tái cấu trúc, có thể tự hỏi:

1. Hai đoạn mã giống nhau có thực sự biểu diễn cùng một quy tắc hoặc cùng một ý định không?
2. Khi yêu cầu thay đổi, các đoạn mã này có cần thay đổi cùng nhau không?
3. Ai hoặc bộ phận nào sở hữu chính sách đó?
4. Abstraction dự kiến có tên đơn giản và API dễ hiểu không?
5. Tách lớp có làm giảm phụ thuộc, hay chỉ tạo thêm wrapper và chuyển tiếp phương thức?
6. Có thể viết kiểm thử để xác nhận hành vi trước và sau tái cấu trúc không?

Một thao tác refactoring đáng thực hiện khi lợi ích dài hạn — giảm rủi ro sai lệch, làm rõ ranh giới, giảm chi phí thay đổi hoặc giúp kiểm thử độc lập — lớn hơn chi phí tạo abstraction và bảo trì nó. Martin Fowler mô tả refactoring là thay đổi cấu trúc bên trong mà không làm thay đổi hành vi quan sát được; thực hiện qua những bước nhỏ giúp giảm rủi ro và dễ kiểm tra hơn [3].

Một tình huống nên chủ động tránh áp dụng quá mức là hai mô-đun đang có cùng một công thức nhưng đại diện cho hai chính sách được quản lý độc lập. Trong trường hợp đó, giữ hai hàm riêng, đặt tên theo nghiệp vụ và viết kiểm thử riêng có thể dễ hiểu hơn tạo một hàm chung nhiều tham số. Tương tự, nếu một lớp hồ sơ sinh viên có một nhóm phương thức cùng quản lý dữ liệu và hành vi của hồ sơ, không cần tạo một lớp mới cho từng getter hoặc setter.

### 6.1. Quy trình refactoring đề xuất

1. Ghi nhận hành vi hiện tại bằng kiểm thử hoặc ví dụ đầu vào/đầu ra.
2. Xác định chính xác kiến thức hoặc trách nhiệm đang bị đặt sai chỗ.
3. Thực hiện thay đổi nhỏ, không thay đổi hành vi quan sát được.
4. Chạy lại kiểm thử và so sánh kết quả.
5. Đánh giá xem cấu trúc mới có dễ đọc và dễ thay đổi hơn không.
6. Dừng khi ranh giới đã rõ; không tiếp tục chia nhỏ chỉ để tăng số lớp hoặc giảm số dòng trùng.

## 7. Kết luận

DRY giúp tránh duy trì cùng một kiến thức ở nhiều nơi; SRP giúp đặt các hành vi có cùng lý do thay đổi vào một thành phần có trách nhiệm rõ ràng. Cả hai đều hướng đến khả năng bảo trì, nhưng áp dụng máy móc có thể tạo ra abstraction sớm, coupling không cần thiết hoặc quá nhiều lớp nhỏ.

Quyết định thiết kế cần dựa trên ý nghĩa nghiệp vụ, nguyên nhân thay đổi, cohesion, coupling và chi phí bảo trì. Mã nguồn tốt không phải là mã không có bất kỳ sự lặp lại nào, cũng không phải chương trình được chia thành nhiều lớp nhất. Mã nguồn tốt là mã có cấu trúc giúp người phát triển hiểu đúng và thay đổi an toàn với độ phức tạp hợp lý.

## 8. Tài liệu tham khảo

Chi tiết nguồn, liên kết và ngày truy cập được liệt kê trong [references.md](references.md).
