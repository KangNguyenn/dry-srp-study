# Code Review — 5 tình huống

Các nhận định dưới đây dựa trên bối cảnh ngắn gọn trong đề bài. Một số tình huống cần xem thêm mã nguồn thực tế trước khi ra quyết định cuối cùng.

| # | Tình huống | Đánh giá | Quyết định |
|---|---|---|---|
| 1 | Hai thao tác dùng cùng chính sách kiểm tra khách hàng | Trùng lặp kiến thức | Dùng chung hàm/chính sách validation; tránh tham số cờ không cần thiết |
| 2 | Thuế và giảm giá có công thức giống nhau nhưng quy tắc nghiệp vụ khác nhau | Có thể chấp nhận | Giữ riêng hai chính sách, đặt tên theo nghiệp vụ và kiểm thử riêng |
| 3 | Student cập nhật thông tin, tính GPA, kiểm tra tình trạng học tập, hiển thị tổng hợp | Vấn đề tiềm ẩn | Kiểm tra nhóm nguyên nhân thay đổi; có thể tách nghiệp vụ học vụ và trình bày khỏi mô hình hồ sơ |
| 4 | StudentNameGetter, StudentNameSetter, StudentAgeGetter, StudentAgeSetter | Áp dụng SRP quá mức | Gộp thao tác dữ liệu đơn giản vào Student hoặc một kiểu hồ sơ phù hợp |
| 5 | OrderService kiểm tra, tính tổng, lưu dữ liệu, gửi email | Nhiều trách nhiệm có khả năng thay đổi độc lập | Tách validator, calculator, repository, sender; giữ OrderService làm lớp điều phối nếu cần |

## Phân tích ngắn

### 1. Shared validation

Nếu hai thao tác thật sự phụ thuộc cùng một chính sách nghiệp vụ, nên có một biểu diễn duy nhất của chính sách đó. Khi quy định đổi, cả hai thao tác dùng ngay logic mới. Phần mở rộng chỉ dành riêng cho từng thao tác nên vẫn giữ độc lập.

### 2. Similar calculations

Hai công thức giống nhau không đủ để kết luận chúng là cùng một quy tắc. Thuế và giảm giá có thể có chủ sở hữu, thời điểm thay đổi và yêu cầu kiểm thử khác nhau. Giữ hai hàm có tên rõ nghĩa giúp tránh ghép hai chính sách không liên quan.

### 3. Many methods

Số lượng phương thức không quyết định SRP. Cần phân loại mỗi phương thức theo trách nhiệm và nguyên nhân thay đổi. Cập nhật thông tin có thể thuộc hồ sơ; tính GPA và kiểm tra học vụ có thể thuộc nghiệp vụ học tập; trình bày tổng hợp có thể thuộc báo cáo/giao diện.

### 4. Too many classes

Getter/setter đơn giản không tạo ra trách nhiệm độc lập chỉ vì chúng là các phương thức khác nhau. Bốn wrapper làm tăng số lượng lớp và tầng điều hướng mà không có lợi ích thay thế rõ ràng.

### 5. Order service

Validation, phép tính, lưu trữ và gửi thông báo thay đổi vì các lý do khác nhau. Tách chúng giúp kiểm thử và thay thế từng phần. Tuy nhiên, lớp điều phối quy trình đặt hàng vẫn có thể hợp lý; không cần tách thêm chỉ để loại bỏ mọi phương thức khỏi service.
